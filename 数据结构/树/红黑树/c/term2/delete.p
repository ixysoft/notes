RB-DELETE (T, z):

# 如果z的左右节点存在NIL节点
if left[z] = nil[T] or right[z] = nil[T]
     then y <- z # z传递给y
     else y <- TREE-SUCCESSOR(z) # 左右节点都不为nil

if left[y] != nil[T]     
    then x <- left[y]
    else x <- right[y]
p[x] <- p[y]
if p[y] = nil[T]
   then root[T] <-  x
   else if y = left[p[y]]
           then left[p[y]] <- x
           else right[p[y]] <- x
if y != z
    then key[z] <- key[y]
          If y has other fields, copy them, too.
if color[y] = BLACK
    then RB-DELETE-FIXUP (T,x)
return y