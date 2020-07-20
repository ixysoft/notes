class Node:
    def __init__(self,newval):
        self.val = newval
        self.left = NullNode()
        self.right = NullNode()
        self.parent = None
        self.color = 'red'

class NullNode:
    def __init__(self):
        self.val = None
        self.left = None
        self.right = None
        self.parent = None
        self.color = 'black'