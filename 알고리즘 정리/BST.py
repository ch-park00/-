import random
class node(object):
    def __init__(self,data):
        self.data=data
        self.left=self.right=None
        

class BST(object):
    def __init__(self):
        self.node=None
        self.root=None
        
    def add_node(self, data):
        new1=node(data)
        if self.root is None:
            self.root=new1
            return
        else:
            tmp=self.root
            while tmp is not None:
                if tmp.data<data:
                    if tmp.right is None:
                        tmp.right=new1
                        return
                    else:
                        tmp=tmp.right
                else:
                    if tmp.left is None:
                        tmp.left=new1
                        return
                    tmp=tmp.left
    def find_node(self,data):
        tmp=self.root
        while tmp is not None:
            if tmp.data==data:
                break
            elif tmp.data>data:
                tmp=tmp.left
            else:
                tmp=tmp.right
        return tmp
    
    def find_suc(self,start):
        suc=start.right
        prev_suc=start
        while suc is not None:
            if suc.left is None:
                break
            prev_suc=suc
            suc=suc.left
            
        if suc==start.right:
            start.right=suc.right
        else:
            prev_suc.left=suc.right
        print("suc data:", suc.data)
        return suc
            
            
    def delete_node(self,data):
        del_node=self.find_node(data)
        print(del_node.data)
        if del_node is None:
            return
        if del_node==self.root:
            if del_node.left is None:
                if del_node.right is None:
                    self.root=None
                    del(del_node)
                    
                else:
                    self.root=del_node.right
                    del(del_node)
                return
            else:
                if del_node.right is None:
                    self.root=del_node.left
                    del(del_node)
                else:
                    # ??부�??�성 ?�요
                    suc=self.find_suc(del_node)
                    suc.left=del_node.left
                    suc.right=del_node.right
                    del(del_node)
                    return
        else:
            prev_node=self.root
            while True:
                if prev_node.left==del_node or prev_node.right==del_node:
                    break
                if prev_node.data>del_node.data:
                    prev_node=prev_node.left
                else:
                    prev_node=prev_node.right
            
            if del_node.left is None:
                if del_node.right is None:
                    if prev_node.left==del_node:
                        prev_node.left=None
                    else:
                        prev_node.right=None
                    del(del_node)
                else:
                    if prev_node.left==del_node:
                        prev_node.left=del_node.right
                    else:
                        prev_node.right=del_node.right
                    del(del_node)
            else:
                if del_node.right is None:
                    if prev_node.left==del_node:
                        prev_node.left=del_node.left
                    else:
                        prev_node.right=del_node.left
                    del(del_node)
                else:
                    # ??부�??�성 ?�요
                    suc=self.find_suc(del_node)
                    suc.left=del_node.left
                    suc.right=del_node.right
                    del(del_node)
                    return
                    
            
    def inorder(self,node):
        if node is None:
            return
        self.inorder(node.left)
        print(node.data)
        self.inorder(node.right)
        
my=BST()
s_data=list(range(1,11))
random.shuffle(s_data)
for i in s_data:
    my.add_node(i)
    print(i)
    
my.delete_node(3)

print("-------------")
my.inorder(my.root)