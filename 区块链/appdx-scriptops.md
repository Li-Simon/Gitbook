# 第四节 交易脚本语言操作符，常量和符号

以下的表和描述参见[https://en.bitcoin.it/wiki/Script](https://en.bitcoin.it/wiki/Script)

表1.脚本压入堆栈

| 符号 | 值 \(十六进制\) | 描述 |
| --- | --- | --- |
| OP\_0 or OP\_FALSE | 0x00 | 一个字节空串被压入堆栈中 |
| 1-75 | 0x01-0x4b | 把接下来的N 个字节压入堆栈中，N 的取值在1 到75 之间 |
| OP\_PUSHDATA1 | 0x4c | 下一个脚本字节包括N，会将接下来的N 个字节压入堆栈 |
| OP\_PUSHDATA2 | 0x4d | 下两个脚本字节包括N，会将接下来的N 个字节压入堆栈 |
| OP\_PUSHDATA4 | 0x4e | 下四个脚本字节包括N，会将接下来的N 个字节压入堆栈 |
| OP\_1NEGATE | 0x4f | 将脚本-1 压入堆栈 |
| OP\_RESERVED | 0x50 | 终止- 交易无效（除非在未执行的OP\_IF语句中） |
| OP\_1 or OP\_TRUE | 0x51 | 将脚本1 压入堆栈 |
| OP\_2 to OP\_16 | 0x52 to 0x60 | 将脚本N 压入堆栈，例如OP\_2 压入脚本“2” |

表2.有条件的流控制的操作符

| 符号 | 值 \(十六进制\) | 描述 |
| --- | --- | --- |
| OP\_NOP | 0x61 | 无操作 |
| OP\_VER | 0x62 | 终止- 交易无效（除非在未执行的OP\_IF 语句中） |
| OP\_IF | 0x63 | 如果栈项元素值为0，语句将被执行 |
| OP\_NOTIF | 0x64 | 如果栈项元素值不为0，语句将被执行 |
| OP\_VERIF | 0x65 | 终止- 交易无效 |
| OP\_VERNOTIF | 0x66 | 终止- 交易无效 |
| OP\_ELSE | 0x67 | 如果前述的OP\_IF 或OP\_NOTIF 或OP\_ELSE 未被执行，这些语句就会被执行 |
| OP\_ENDIF | 0x68 | 终止OP\_IF, OP\_NOTIF, OP\_ELSE 区块 |
| OP\_VERIFY | 0x69 | 如果栈项元素值非真，则标记交易无效 |
| OP\_RETURN | 0x6a | 标记交易无效 |

表3.时间锁操作符

| 符号 | 值 \(十六进制\) | 描述 |
| --- | --- | --- |
| OP\_CHECKLOCKTIMEVERIFY \(previously OP\_NOP2\) | 0xb1 | 如果栈顶元素比交易锁定时间字段大，则将交易标记为无效。否则脚本评测将像OP\_NOP操作一样继续执行。交易在一下4种之一的情况下是无效的：1.堆栈是空的；2.栈顶元素是负数；3.当交易锁定时间字段值少于500000000时，栈顶元素大于等于500000000，反之亦然；4.输入序列字段等于0xffffffff。具体内容详见BIP-65。 |
| OP\_CHECKSEQUENCEVERIFY \(previously OP\_NOP3\) | 0xb2 | 如果输入值\(BIP 0068强制规定的顺序\)的相对锁定时间不等于或多于栈顶元素值时，将交易标记为无效。具体内容详见BIP-112。 |

表4.堆栈操作符

| 符号 | 值 \(十六进制\) | 描述 |
| --- | --- | --- |
| OP\_TOALTSTACK | 0x6b | 从主堆栈中取出元素，推入辅堆栈。 |
| OP\_FROMALTSTACK | 0x6c | 从辅堆栈中取出元素，推入主堆栈 |
| OP\_2DROP | 0x6d | 移除栈顶两个元素 |
| OP\_2DUP | 0x6e | 复制栈顶两个元素 |
| OP\_3DUP | 0x6f | 复制栈顶三个元素 |
| OP\_2OVER | 0x70 | 把栈底的第三、第四个元素拷贝到栈顶 |
| OP\_2ROT | 0x71 | 移动第五、第六元素到栈顶 |
| OP\_2SWAP | 0x72 | 将栈顶的两个元素进行交换 |
| OP\_IFDUP | 0x73 | 如果栈项元素值不为0，复制该元素值 |
| OP\_DEPTH | 0x74 | Count the items on the stack and push the resulting count |
| OP\_DROP | 0x75 | 删除栈顶元素 |
| OP\_DUP | 0x76 | 复制栈顶元素 |
| OP\_NIP | 0x77 | 删除栈顶的下一个元素 |
| OP\_OVER | 0x78 | 复制栈顶的下一个元素到栈顶 |
| OP\_PICK | 0x79 | 把堆栈的第n 个元素拷贝到栈顶 |
| OP\_ROLL | 0x7a | 把堆栈的第n 个元素移动到栈顶 |
| OP\_ROT | 0x7b | 翻转栈顶的三个元素 |
| OP\_SWAP | 0x7c | 栈顶的三个元素交换 |
| OP\_TUCK | 0x7d | 拷贝栈顶元素并插入到栈顶第二个元素之后 |

表5.字符串接操作

| 符号 | 值 \(十六进制\) | 描述 |
| --- | --- | --- |
| _OP\_CAT_ | 0x7e | 连接两个字符串，已禁用 |
| _OP\_SUBSTR_ | 0x7f | 返回字符串的一部分，已禁用 |
| _OP\_LEFT_ | 0x80 | 在一个字符串中保留左边指定长度的子串，已禁用 |
| _OP\_RIGHT_ | 0x81 | 在一个字符串中保留右边指定长度的子串，已禁用 |
| OP\_SIZE | 0x82 | 把栈顶元素的字符串长度压入堆栈 |

表6.二进制算术和条件

| 符号 | 值 \(十六进制\) | 描述 |
| --- | --- | --- |
| _OP\_INVERT_ | 0x83 | 所有输入的位取反，已禁用 |
| _OP\_AND_ | 0x84 | 对输入的所有位进行布尔与运算，已禁用 |
| _OP\_OR_ | 0x85 | 对输入的每一位进行布尔或运算，已禁用 |
| _OP\_XOR_ | 0x86 | 对输入的每一位进行布尔异或运算，已禁用 |
| OP\_EQUAL | 0x87 | 如果输入的两个数相等，返回1，否则返回0 |
| OP\_EQUALVERIFY | 0x88 | 与OP\_EQUAL 一样，如结果为0，之后运行OP\_VERIFY |
| OP\_RESERVED1 | 0x89 | 终止- 无效交易（除非在未执行的OP\_IF 语句中） |
| OP\_RESERVED2 | 0x8a | 终止-无效交易（除非在未执行的OP\_IF 语句中） |

表7.数值操作

| 符号 | 值 \(十六进制\) | 描述 |
| --- | --- | --- |
| OP\_1ADD | 0x8b | 栈顶值加1 |
| OP\_1SUB | 0x8c | 栈顶值减1 |
| _OP\_2MUL_ | 0x8d | 无效（栈顶值乘2） |
| _OP\_2DIV_ | 0x8e | 无效（栈顶值除2） |
| OP\_NEGATE | 0x8f | 栈顶值符号取反 |
| OP\_ABS | 0x90 | 栈顶值符号取正 |
| OP\_NOT | 0x91 | 如果栈顶值为0 或1，则输出1或0；否则输出0 |
| OP\_0NOTEQUAL | 0x92 | 输入值为0 输出0；否则输出1 |
| OP\_ADD | 0x93 | 弹出栈顶的两个元素，压入二者相加结果 |
| OP\_SUB | 0x94 | 弹出栈顶的两个元素，压入二者相减（第二项减去第一项）结果 |
| OP\_MUL | 0x95 | 禁用（栈顶两项的积） |
| OP\_DIV | 0x96 | 禁用（输出用第二项除以第一项的倍数） |
| OP\_MOD | 0x97 | 禁用（输出用第二项除以第一项得到的余数） |
| OP\_LSHIFT | 0x98 | 禁用（左移第二项，移动位数为第一项的二进制位数） |
| OP\_RSHIFT | 0x99 | 禁用（右移第二项，移动位数为第一项的二进制位数） |
| OP\_BOOLAND | 0x9a | 布尔与运算，两项都不为0，输出1，否则输出0 |
| OP\_BOOLOR | 0x9b | 布尔或运算，两项有一个不为0，输出1，否则输出0 |
| OP\_NUMEQUAL | 0x9c | 两项相等则输出1，否则输出为0 |
| OP\_NUMEQUALVERIFY | 0x9d | 与NUMEQUAL 相同，如结果为0运行OP\_VERIFY |
| OP\_NUMNOTEQUAL | 0x9e | 如果栈顶两项不是相等数的话，则输出1 |
| OP\_LESSTHAN | 0x9f | 如果第二项小于栈顶项，则输出1 |
| OP\_GREATERTHAN | 0xa0 | 如果第二项大于栈顶项，则输出1 |
| OP\_LESSTHANOREQUAL | 0xa1 | 如果第二项小于或等于第一项，则输出1 |
| OP\_GREATERTHANOREQUAL | 0xa2 | 如果第二项大于或等于第一项，则输出1 |
| OP\_MIN | 0xa3 | 输出栈顶两项中较小的一项 |
| OP\_MAX | 0xa4 | 输出栈顶两项中较大的一项 |
| OP\_WITHIN | 0xa5 | 如果第三项的数值介于前两项之间，则输出1 |

表8.加密和散列操作

| 符号 | 值 \(十六进制\) | 描述 |
| --- | --- | --- |
| OP\_RIPEMD160 | 0xa6 | 返回栈顶项的RIPEMD160 哈希值 |
| OP\_SHA1 | 0xa7 | 返回栈顶项SHA1 哈希值 |
| OP\_SHA256 | 0xa8 | 返回栈顶项SHA256 哈希值 |
| OP\_HASH160 | 0xa9 | 栈顶项进行两次HASH，先用SHA-256，再用RIPEMD-160 |
| OP\_HASH256 | 0xaa | 栈顶项用SHA-256 算法HASH 两次 |
| OP\_CODESEPARATOR | 0xab | 标记已进行签名验证的数据 |
| OP\_CHECKSIG | 0xac | 交易所用的签名必须是哈希值和公钥的有效签名，如果为真，则返回1 |
| OP\_CHECKSIGVERIFY | 0xad | 与CHECKSIG 一样，但之后运行OP\_VERIFY |
| OP\_CHECKMULTISIG | 0xae | 对于每对签名和公钥运行CHECKSIG。所有的签名要与公钥匹配。因为存在BUG，一个未使用的外部值会从堆栈中删除。 |
| OP\_CHECKMULTISIGVERIFY | 0xaf | 与CHECKMULTISIG 一样，但之后运行OP\_VERIFY |

表9.非操作符

| 符号 | 值 \(十六进制\) | 描述 |
| --- | --- | --- |
| OP\_NOP1-OP\_NOP10 | 0xb0-0xb9 | 无操作忽略 |

表10.仅供内部使用的保留关键字

| 符号 | 值 \(十六进制\) | 描述 |
| --- | --- | --- |
| OP\_SMALLDATA | 0xf9 | 代表小数据域 |
| OP\_SMALLINTEGER | 0xfa | 代表小整数数据域 |
| OP\_PUBKEYS | 0xfb | 代表公钥域 |
| OP\_PUBKEYHASH | 0xfd | 代表公钥哈希域 |
| OP\_PUBKEY | 0xfe | 代表公钥域 |
| OP\_INVALIDOPCODE | 0xff | 代表当前未指定的操作码 |



