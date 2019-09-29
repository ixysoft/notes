# commit乱码
最近在电脑上使用MobaXterm,使用`git commit`提交代码时,中文的注释总是变成数字形式,用户体验极差,经过google查询之后,找到了方案:
```
git config --global core.quotepath false
```
或者手动修改~/.gitconfig,添加:
```
[core]
quotepath = false
```
