#/bin/bash
#

#
# Bash Shell定义文字颜色有三个参数：Style，Frontground和Background，每个参数有7个值，意义如下：
# 0：黑 
# 1：红 
# 2：绿 
# 3：黄 
# 4：蓝 
# 5：紫 
# 6：深绿 
# 7：白
#
# 其中，+30表示前景色，+40表示背景色
#
# 这里提供一段代码可以打印颜色表：
#

for STYLE in 0 1 2 3 4 5 6 7; do
  for FG in 30 31 32 33 34 35 36 37; do
    for BG in 40 41 42 43 44 45 46 47; do
      CTRL="\033[${STYLE};${FG};${BG}m"
      echo -en "${CTRL}"
      echo -n "${STYLE};${FG};${BG}"
      echo -en "\033[0m"
    done
    echo
  done
  echo
done
# Reset
echo -e "\033[0m"
