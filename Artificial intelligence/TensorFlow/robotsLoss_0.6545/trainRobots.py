# This example shows classification of colours (r/y/g/c/b/m) using the softmax function.
# Data is read from a file and loss is written to disk for display in TensorBoard.
# This version saves the model state and continues where it left off.

import tensorflow as tf
import os

BOARD_SIZE_X = 12
BOARD_SIZE_Y = 12
LENGTH_OF_PROGRAM = 4

def load_data(filename, no_of_records):
    filename_queue = tf.train.string_input_producer([filename])
    reader = tf.TFRecordReader()
    _, serialized = reader.read(filename_queue)
    features = tf.parse_single_example(serialized, features = {\
        "program": tf.FixedLenFeature([], tf.string),\
        "boards": tf.FixedLenFeature([], tf.string)})
    program_raw = tf.decode_raw(features['program'], tf.uint8)
    program = tf.cast(tf.reshape(program_raw, [4]), tf.int32)
    boards_raw = tf.decode_raw(features['boards'], tf.uint8)
    boards = tf.cast(tf.reshape(boards_raw, [3 * BOARD_SIZE_X * BOARD_SIZE_Y]), tf.float32)
    # this causes records to be read
    return tf.train.batch([boards, program], no_of_records)

def getBatches():
    sess = tf.Session() 
    sess.run(tf.global_variables_initializer())
    X, Y = load_data("./records/training_set.tfrecord", 1000)
    Xt, Yt = load_data("./records/test_set.tfrecord", 100)

    coord = tf.train.Coordinator()
    # queue runner for filename queue
    threads = tf.train.start_queue_runners(sess=sess, coord=coord)

    coord.request_stop()
    coord.join(threads)
    sess.close()

    return (X,Y,Xt,Yt)


# initialize variables/model parameters
W = tf.Variable(tf.zeros([16, 432]), name="weights")
b = tf.Variable(tf.zeros([16]), name="bias")

learning_rate = 0.3
training_steps = 5000
initial_step = 0

# define the training loop operations
def combine(X):
    # combine data X with variables and return the result
    return tf.reshape(tf.transpose(tf.matmul(W, X, transpose_b = True)) + b, [-1,4,4])

def inference(X):
    # compute inference model over data X and return the result
    return tf.nn.softmax(combine(X))

def loss(X, Y):
    # compute loss over training data X and expected outputs Y
    return tf.reduce_mean(tf.nn.sparse_softmax_cross_entropy_with_logits(logits = combine(X), labels = Y))

def train(loss_func):
    # train / adjust model parameters according to computed total loss
    return tf.train.GradientDescentOptimizer(learning_rate).minimize(loss_func)

def evaluate(sess, X, Y, Xt, Yt):
    # evaluate the resulting trained model
    predicted = tf.to_int32(tf.arg_max(inference(X), 1))
    print("Training fraction classified correctly: ", sess.run(tf.reduce_mean(tf.cast(tf.equal(predicted, Y), tf.float32))))

    predicted = tf.to_int32(tf.arg_max(inference(Xt), 1))
    print("Test fraction classified correctly: ", sess.run(tf.reduce_mean(tf.cast(tf.equal(predicted, Yt), tf.float32))))


# create a saver
saver = tf.train.Saver()

# launch the graph in a session, setup boilerplate
sess = tf.Session() 
sess.run(tf.global_variables_initializer())

X,Y,Xt,Yt = getBatches()

loss_func = loss(X, Y)
train_op = train(loss_func)
coord = tf.train.Coordinator()
# queue runner for filename queue
threads = tf.train.start_queue_runners(sess=sess, coord=coord)
# define scalar to be used in summary
summary = tf.summary.scalar("loss", loss_func)
writer = tf.summary.FileWriter("myGraph", sess.graph)

# verify if we don't have a checkpoint saved already
ckpt = tf.train.get_checkpoint_state("./data")
if ckpt and ckpt.model_checkpoint_path:
    # Restores from checkpoint
    saver.restore(sess, ckpt.model_checkpoint_path)
    initial_step = int(ckpt.model_checkpoint_path.rsplit('-', 1)[1])

# actual training loop
for step in range(training_steps):
    sess.run(train_op)
    # log loss every step for visualisation in TensorBoard
    writer.add_summary(sess.run(summary), step + initial_step)
    # for debugging and learning purposes, see how the loss gets decremented thru training steps
    if step % 100 == 0:
        print("step:",step,"loss: ", sess.run(loss_func))

# print results
print("W: ", sess.run(W))
print("b: ", sess.run(b))

# save the model
saver.save(sess, "./data/my-model", global_step = training_steps + initial_step)

evaluate(sess, X, Y, Xt, Yt)
coord.request_stop()
coord.join(threads)
writer.close()
sess.close()




