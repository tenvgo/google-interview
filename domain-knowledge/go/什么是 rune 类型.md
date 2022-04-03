# [Go] 什么是 rune 类型
ASCII 码只需要 7 bit 就可以完整地表示，但只能表示英文字母在内的128个字符，为了表示世界上大部分的文字系统，发明了 Unicode， 它是ASCII的超集，包含世界上书写系统中存在的所有字符，并为每个代码分配一个标准编号（称为Unicode CodePoint），在 Go 语言中称之为 rune，是 int32 类型的别名。

Go 语言中，字符串的底层表示是 byte (8 bit) 序列，而非 rune (32 bit) 序列。例如下面的例子中 `语` 和 `言` 使用 UTF-8 编码后各占 3 个 byte，因此 `len("Go语言")` 等于 8，当然我们也可以将字符串转换为 rune 序列。

```go
fmt.Println(len("Go语言")) // 8
fmt.Println(len([]rune("Go语言"))) // 4
```