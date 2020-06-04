#coding:utf8
class Solution:
    '''
    判断是否匹配给定的模式

    >>> import sys
    >>> sys.setrecursionlimit(10000000)
    >>> s = Solution()
    >>> s.isMatch('apppppppl','ap*l')
    True
    >>> s.isMatch('apa','app')
    False
    >>> a = 'a{b}c{d}e'.format(b='j'*10000,d='o'*5)
    >>> s.isMatch(a,'a')
    False
    >>> s.isMatch(a,'ab*cd*e')
    False
    >>> s.isMatch(a,'aj*co*e')
    True
    '''
    def isMatch(self,s,p):
        if not p: # p为空
            return not s # 如果s为空,则匹配成功,否则失败
        
        # 获取第一个字节的匹配情况,s为空,返回false,s不为空,字符相同或为.匹配成功,否则失败
        first_char_match = bool(s) and p[0] in {s[0],'.'}
        if len(p) > 1 and p[1] == '*':  # p的长度大于1
            return (self.isMatch(s,p[2:]) or first_char_match and self.isMatch(s[1:],p))
        else:
            return first_char_match and self.isMatch(s[1:],p[1:])

if __name__ == '__main__':
    import doctest
    doctest.testmod()