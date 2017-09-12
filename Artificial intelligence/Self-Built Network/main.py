class Node:

    def __init__(self, Link, value):
        self.value = value
        self.Link = Link

        if Link is not [] and value is 0:
            for l in Link:
                self.value += l.weight * l.node.value

class Link:

    def __init__(self, node = [], weight = 1):
        self.node = node
        self.weight = weight


links = []
#fields
values = [1,2,3,4]
#x is de input array
#outputAnswers is de correcte gegeven antwoord array
outputAnswers = [5, 6]
#outputAnswers is de placeholder
outputNodes = []

for val in values:
    links.append(Link(Node([], val)))

for x in outputAnswers:
    outputNodes.append(Node(links, 0))

def inference(x):
#creeer in en output nodes
    output = []
    for Onode in outputNodes:
        output.append(sum([l.weight * l.node.value for l in Onode.Link]))
    return(output)

def loss(y, ycorrect):
    #if (len(y) != len(ycorrect)):
        #raise ValueError("The amount of values in y doesn match the amount of values in ycorrect")

    loss = 0
    for i in range(len(y)):
        loss += ((y[i] - ycorrect[i]) * (y[i] - ycorrect[i]))

    return loss
print(inference(values))
print(loss(inference(values), outputAnswers))
