import tensorflow as tf
import os
from createBoardAndProgram import *

BOARD_SIZE_X = 12
BOARD_SIZE_Y = 12
LENGTH_OF_PROGRAM = 4

sess = None

# initialize variables/model parameters
W = tf.Variable(tf.zeros([16, 432]), name="weights")
b = tf.Variable(tf.zeros([16]), name="bias")

def init():
    # your code to load the trained neural network into memory
    global sess,W,b
    saver = tf.train.Saver()
    sess = tf.Session() 
    sess.run(tf.global_variables_initializer())
    
    # verify if we don't have a checkpoint saved already
    ckpt = tf.train.get_checkpoint_state("./data")
    if ckpt and ckpt.model_checkpoint_path:
        # Restores from checkpoint
        saver.restore(sess, ckpt.model_checkpoint_path)
    

# define the training loop operations
def combine(X):
    # combine data X with variables and return the result
    matmul = tf.matmul(W, X, transpose_b = True)
    transposedMatmul = tf.transpose(matmul)
    return tf.reshape(transposedMatmul + b, [4,4])

def inference(X):
    # compute inference model over data X and return the result
    return tf.nn.softmax(combine(X))

# Obstacle board, start position board, goal position board
def solve(boxBoard, startBoard, goalBoard):
    X = tf.reshape(tf.cast([boxBoard, startBoard, goalBoard], tf.float32), [1, 3 * BOARD_SIZE_X * BOARD_SIZE_Y])
    return list(sess.run(tf.to_int32(tf.arg_max(inference(X), 1))))


def test():
    board, startX, startY, goalX, goalY, program = createBoardAndProgram(BOARD_SIZE_X, BOARD_SIZE_Y, 10, 4)
    startBoard = [[0] * BOARD_SIZE_X for i in range(BOARD_SIZE_Y)]
    startBoard[startY][startX] = 1
    goalBoard = [[0] * BOARD_SIZE_X for i in range(BOARD_SIZE_Y)]
    goalBoard[goalY][goalX] = 1
    program = solve(board, startBoard, goalBoard)

init()
#test()

                    
