class RBT:
    # y为删除掉的节点,x为current节点
    def delete(self,tree,n)
        delTree = self.search(tree,n) # 查找需要删除的节点
        if delTree is None: # 节点不存在
            self.missNode += 1
            return
        self.deleteNode +=1 # 删除的节点数+1

        y = delTree # y为需要删除的节点
        yorgcolor = y.color # 需要删除节点的颜色

        if delTree.left.val is None:    # 需要删除的节点左孩子不存在
            x = delTree.right # 假定右孩子为替换节点
            self.transplant(delTree,delTree.right) # 将右子树移动到需要删除的节点位置
        elif delTree.right.val is None:
            x = delTree.left
            self.transplant(delTree,delTree.left) # 将左孩子移动到需要删除的节点位置
        else:
            y = self.findMinimum(delTree.right) # 将y设定为替死鬼节点(右子树中的最小节点)
            y.orgcolor = y.color # 需要删除节点的颜色
            x = y.right # 需要删除节点的右节点可能存在,需要将它移动到y的位置

            if y.parent is delTree: # 需要删除的节点为原本需要删除节点的子节点
                x.parent = delTree.right # 把x的父节点设置为y????
            else:
                self.transplant(y,y.right) # y右子节点替换到当前位置
                y.right = delTree.right # y的右节点设置为delTree的右节点
                y.right.parent = y # 架空delTree节点
        
            self.transplant(delTree,y) # 架空delTree
            y.left = delTree.left # 把y的左节点设置为delTree的左节点,说明最后会把delTree删除掉
            y.left.parent = y
            y.color = delTree.color # 将delTree的颜色给y
        if yorgcolor == 'black':    # 需要删除节点的颜色为黑色,破坏了RB的规则
            self.RBT_Delete_Fixup(self,x) # 通过current来修复红黑树

    # 删除操作修复,x为current
    def RBT_Delete_Fixup(self,tree,x):
        # x非根节点,且x的颜色为黑色
        # transplant会自动判断当前节点是否为根节点
        """
        x为root可能的情况:
            [y]
            /
          [x]
        与其对称的情况同理
        """
        # x为红色时,将其转变成黑色即可,这种情况也不考虑,因为我们在delete的时候,已经把删除节点变成了一个最多只有一个孩子的节点了,其没有兄弟节点
        while x is not tree.root and x.color == 'black':
            if x == x.parent.left: # 替换节点在父节点左侧
                w = x.parent.right # 替换节点的兄弟节点

                # case1,兄弟是红节点
                if w.color == "red":    # 兄弟为红色
                    # 因为被删除的节点位于父节点左侧,所以左侧黑节点比右侧少1,我们可以利用红色节点来为左侧节点增高
                    # 因为w的颜色是红色,所以父节点为黑色.
                    w.color = "black"
                    x.parent.color = "red"
                    self.left_rotate(tree,x.parent) # 左旋父节点
                    w = x.parent.right # 兄弟节点变成了x.parent.right.left
                
                # case2,兄弟节点为黑节点,并且两个孩子也是黑色的
                if w.left.color == "black" and w.right.color == 'black':
                    w.color = 'red' # 将兄弟节点设置为红色
                    x = x.parent # 将x替换成x的父节点
                # 进过case2,x.parent的左右两侧都少了一个节点,此刻一定是不平衡的

                # case3,兄弟节点子节点左红右黑
                else:
                    if w.right.color == 'black': # 暗示左节点为红色,否则就进之前的if了
                        w.left.color = 'black' # 将兄弟节点左节点编程黑色,此刻其左孩子黑高度升高
                        w.color = 'red' # 兄弟节点变红色,其黑高度降低
                        self.right_rotate(tree,w) # 沿兄弟节点右旋,此时以w左节点为核心的新子树黑高度恢复
                        w = x.parent.right # 将兄弟节点设置为x父节点的右节点(更新兄弟节点)(原兄弟节点的左节点)
                    
                    # case4,兄弟节点右节点为红色,左节点不论
                    w.color = x.parent.color # 将兄弟节点颜色设置为父节点颜色,此处原因可以分情况讨论
                    x.parent.color = 'black' # 将父节点的颜色设置为黑色
                    w.right.color = 'black' # 兄弟节点右节点设置为黑色
                    # TODO:
                    self.left_rotate(tree,x.parent) # 绕x的父节点左旋
                    x = tree.root
