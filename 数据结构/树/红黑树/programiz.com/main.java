// Implementing Red-Black Tree in Java

class Node {
  int data;
  Node parent;
  Node left;
  Node right;
  int color;
}

public class RedBlackTree {
  private Node root;
  private Node TNULL; //叶子节点

  // Preorder
  private void preOrderHelper(Node node) {
    if (node != TNULL) {
      System.out.print(node.data + " ");
      preOrderHelper(node.left);
      preOrderHelper(node.right);
    }
  }

  // Inorder
  private void inOrderHelper(Node node) {
    if (node != TNULL) {
      inOrderHelper(node.left);
      System.out.print(node.data + " ");
      inOrderHelper(node.right);
    }
  }

  // Post order
  private void postOrderHelper(Node node) {
    if (node != TNULL) {
      postOrderHelper(node.left);
      postOrderHelper(node.right);
      System.out.print(node.data + " ");
    }
  }

  // Search the tree
  private Node searchTreeHelper(Node node, int key) {
    if (node == TNULL || key == node.data) {
      return node;
    }

    if (key < node.data) {
      return searchTreeHelper(node.left, key);
    }
    return searchTreeHelper(node.right, key);
  }

  // Balance the tree after deletion of a node
  private void fixDelete(Node x) {
    Node s;
    while (x != root && x.color == 0) {
      if (x == x.parent.left) {
        s = x.parent.right;
        if (s.color == 1) {
          s.color = 0;
          x.parent.color = 1;
          leftRotate(x.parent);
          s = x.parent.right;
        }

        if (s.left.color == 0 && s.right.color == 0) {
          s.color = 1;
          x = x.parent;
        } else {
          if (s.right.color == 0) {
            s.left.color = 0;
            s.color = 1;
            rightRotate(s);
            s = x.parent.right;
          }

          s.color = x.parent.color;
          x.parent.color = 0;
          s.right.color = 0;
          leftRotate(x.parent);
          x = root;
        }
      } else {
        s = x.parent.left;
        if (s.color == 1) {
          s.color = 0;
          x.parent.color = 1;
          rightRotate(x.parent);
          s = x.parent.left;
        }

        if (s.right.color == 0 && s.right.color == 0) {
          s.color = 1;
          x = x.parent;
        } else {
          if (s.left.color == 0) {
            s.right.color = 0;
            s.color = 1;
            leftRotate(s);
            s = x.parent.left;
          }

          s.color = x.parent.color;
          x.parent.color = 0;
          s.left.color = 0;
          rightRotate(x.parent);
          x = root;
        }
      }
    }
    x.color = 0;
  }

  //v代替u的位置
  private void rbTransplant(Node u, Node v) {
    if (u.parent == null) {
      root = v;
    } else if (u == u.parent.left) {
      u.parent.left = v;
    } else {
      u.parent.right = v;
    }
    v.parent = u.parent;
  }

  //删除节点
  private void deleteNodeHelper(Node node, int key) {
    Node z = TNULL;
    Node x, y;
    while (node != TNULL) {
      if (node.data == key) { //需要删除的节点为根节点
        z = node; //将根节点设为z
      }

      if (node.data <= key) { //需要删除的节点处于node右侧
        node = node.right;
      } else {  //需要删除的节点位于节点左侧
        node = node.left;
      }
    }

    if (z == TNULL) { //需要删除的节点不存在
      System.out.println("Couldn't find key in the tree");
      return;
    }

    y = z;  //将需要删除的节点存入y
    int yOriginalColor = y.color; //保存需要删除节点的颜色
    if (z.left == TNULL) {  //如果需要删除的节点不存在左节点
      x = z.right;          //x存入右节点
      rbTransplant(z, z.right); //将右节点存入z
    } else if (z.right == TNULL) {  //右节点为NULL
      x = z.left;         //x存入左节点
      rbTransplant(z, z.left);  //将左节点存入z
    } else {
      y = minimum(z.right);     //记录右侧最小节点
      yOriginalColor = y.color; //保存右侧最小节点的颜色
      x = y.right;              //将最小节点的右节点存入x
      if (y.parent == z) {      //最小节点的父节点为需要删除的节点
        x.parent = y;         //将最小节点右节点的父节点设置为y
      } else {
        rbTransplant(y, y.right); //将最小节点的右节点存入y的位置
        y.right = z.right;        //需要删除的节点的右节点当做最小节点的右节点
        y.right.parent = y;     //并将右侧的元素父节点设置为最小节点
      }

      rbTransplant(z, y);     //将最小节点的值传递到需要删除的节点上
      y.left = z.left;        //最小节点的左节点设定为需要删除节点的左节点
      y.left.parent = y;      //左侧父节点设置最最小节点
      y.color = z.color;      //颜色也传递到最小节点
    }
    if (yOriginalColor == 0) {  //如果最小节点的原始颜色为黑色,此时破坏了整棵树的平衡
      fixDelete(x); //调整c
    }
  }

  // Balance the node after insertion
  private void fixInsert(Node k) {  //进入此处的条件为k.parent.parent存在
    Node u;
    while (k.parent.color == 1) { //默认k为red
      if (k.parent == k.parent.parent.right) {  //位于祖父节点右侧
        u = k.parent.parent.left; //k的叔父节点
        if (u.color == 1) { //假如uncle节点为red,将叔父节点与父节点设置为黑色,祖父节点设置为红色,将祖父节点作为当前节点进行调整
          u.color = 0;
          k.parent.color = 0;
          k.parent.parent.color = 1;
          k = k.parent.parent;
        } else {  //叔父节点为黑色
          if (k == k.parent.left) { //当前节点处于p节点左侧,RRL结构,需要调整为RRR结构
            k = k.parent;
            rightRotate(k); //原k的父节点右旋
          }
          k.parent.color = 0; //k的父节点
          k.parent.parent.color = 1;  //祖父节点设置为红色
          leftRotate(k.parent.parent);  //左旋,整棵树爆出平衡
        }
      } else {  //位于祖父节点左侧
        u = k.parent.parent.right;  //叔父节点

        if (u.color == 1) { //如果叔父节点为红色
          u.color = 0;
          k.parent.color = 0;
          k.parent.parent.color = 1;
          k = k.parent.parent;
        } else {  //叔父节点为黑色
          if (k == k.parent.right) {  //LLR结构,需要绕父节点左旋
            k = k.parent;
            leftRotate(k);
          }
          k.parent.color = 0;
          k.parent.parent.color = 1;
          rightRotate(k.parent.parent); //调整后重新平衡
        }
      }
      if (k == root) {  //如果当前节点为root节点,此时结束
        break;
      }
    }
    root.color = 0; //设定根节点为黑色
  }

  private void printHelper(Node root, String indent, boolean last) {
    if (root != TNULL) {
      System.out.print(indent);
      if (last) {
        System.out.print("R----");
        indent += "   ";
      } else {
        System.out.print("L----");
        indent += "|  ";
      }

      String sColor = root.color == 1 ? "RED" : "BLACK";
      System.out.println(root.data + "(" + sColor + ")");
      printHelper(root.left, indent, false);
      printHelper(root.right, indent, true);
    }
  }

  public RedBlackTree() {
    TNULL = new Node();
    TNULL.color = 0;
    TNULL.left = null;
    TNULL.right = null;
    root = TNULL;
  }

  public void preorder() {
    preOrderHelper(this.root);
  }

  public void inorder() {
    inOrderHelper(this.root);
  }

  public void postorder() {
    postOrderHelper(this.root);
  }

  public Node searchTree(int k) {
    return searchTreeHelper(this.root, k);
  }

  public Node minimum(Node node) {
    while (node.left != TNULL) {
      node = node.left;
    }
    return node;
  }

  public Node maximum(Node node) {
    while (node.right != TNULL) {
      node = node.right;
    }
    return node;
  }

  public Node successor(Node x) {
    if (x.right != TNULL) {
      return minimum(x.right);
    }

    Node y = x.parent;
    while (y != TNULL && x == y.right) {
      x = y;
      y = y.parent;
    }
    return y;
  }

  public Node predecessor(Node x) {
    if (x.left != TNULL) {
      return maximum(x.left);
    }

    Node y = x.parent;
    while (y != TNULL && x == y.left) {
      x = y;
      y = y.parent;
    }

    return y;
  }

  public void leftRotate(Node x) {
    Node y = x.right;
    x.right = y.left;
    if (y.left != TNULL) {
      y.left.parent = x;
    }
    y.parent = x.parent;
    if (x.parent == null) {
      this.root = y;
    } else if (x == x.parent.left) {
      x.parent.left = y;
    } else {
      x.parent.right = y;
    }
    y.left = x;
    x.parent = y;
  }

  public void rightRotate(Node x) {
    Node y = x.left;
    x.left = y.right;
    if (y.right != TNULL) {
      y.right.parent = x;
    }
    y.parent = x.parent;
    if (x.parent == null) {
      this.root = y;
    } else if (x == x.parent.right) {
      x.parent.right = y;
    } else {
      x.parent.left = y;
    }
    y.right = x;
    x.parent = y;
  }

  public void insert(int key) {
    Node node = new Node();
    node.parent = null;
    node.data = key;
    node.left = TNULL;
    node.right = TNULL;
    node.color = 1;

    Node y = null;
    Node x = this.root;

    while (x != TNULL) {
      y = x;
      if (node.data < x.data) {
        x = x.left;
      } else {
        x = x.right;
      }
    }

    node.parent = y;
    if (y == null) {
      root = node;
    } else if (node.data < y.data) {
      y.left = node;
    } else {
      y.right = node;
    }

    if (node.parent == null) {
      node.color = 0;
      return;
    }

    if (node.parent.parent == null) {
      return;
    }

    fixInsert(node);
  }

  public Node getRoot() {
    return this.root;
  }

  public void deleteNode(int data) {
    deleteNodeHelper(this.root, data);
  }

  public void printTree() {
    printHelper(this.root, "", true);
  }

  public static void main(String[] args) {
    RedBlackTree bst = new RedBlackTree();
    bst.insert(55);
    bst.insert(40);
    bst.insert(65);
    bst.insert(60);
    bst.insert(75);
    bst.insert(57);
    bst.printTree();

    System.out.println("\nAfter deleting:");
    bst.deleteNode(40);
    bst.printTree();
  }
}