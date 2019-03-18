HW03
===
This is the hw03 sample. Please follow the steps below.

# Build the Sample Program

1. Fork this repo to your own github account.

2. Clone the repo that you just forked.

3. Under the hw03 dir, use:

	* `make` to build.

	* `make clean` to clean the ouput files.

4. Extract `gnu-mcu-eclipse-qemu.zip` into hw03 dir. Under the path of hw03, start emulation with `make qemu`.

	See [Lecture 02 ─ Emulation with QEMU] for more details.

5. The sample is a minimal program for ARM Cortex-M4 devices, which enters `while(1);` after reset. Use gdb to get more details.

	See [ESEmbedded_HW02_Example] for knowing how to do the observation and how to use markdown for taking notes.

# Build Your Own Program

1. Edit main.c.

2. Make and run like the steps above.

3. Please avoid using hardware dependent C Standard library functions like `printf`, `malloc`, etc.

# HW03 Requirements

1. How do C functions pass and return parameters? Please describe the related standard used by the Application Binary Interface (ABI) for the ARM architecture.

2. Modify main.c to observe what you found.

3. You have to state how you designed the observation (code), and how you performed it.

	Just like how you did in HW02.

3. If there are any official data that define the rules, you can also use them as references.

4. Push your repo to your github. (Use .gitignore to exclude the output files like object files or executable files and the qemu bin folder)

[Lecture 02 ─ Emulation with QEMU]: http://www.nc.es.ncku.edu.tw/course/embedded/02/#Emulation-with-QEMU
[ESEmbedded_HW02_Example]: https://github.com/vwxyzjimmy/ESEmbedded_HW02_Example

--------------------

- [x] **If you volunteer to give the presentation next week, check this.**

--------------------

**★★★ Please take your note here ★★★**
##設計
因為這次作業內容是要觀察c函式如何**傳送**跟**回傳**，
於是我就在main函式中用了一個自定義的函式**pluse_fun**來將參數傳出以便觀察~
由disassemble後的結果可以對每行組合語言作分析，來觀察編譯器的行為(*右邊紫色的字為每行組語做的事情的注釋*)
(以下的編號皆以圖上為準)
13.電腦會先給宣告好的a,b,c變數一個位置(0054~005c)
7.為了取用在13留好空間的各變數，在7這邊分別存了a,b,c的地址
1.電腦拿取變數的方式為 用**ldr r3,pc加上相對位置來 將各變數的地址載入r3**(相對位址會由電腦自動算出)
                         **再用 ldr  rx,r3 將該變數載入rx暫存器**
2.拿到 a(r2),b(r3)後，存到r0(a),r1(b)，算是正式的取用a,b，**並用r0,r1傳給pluse_fun用**
8.進到pluse_fun後，先用 sub sp #12 在stake中空出可以用的空間
9.用 *str* 將r0(a),r1(b) 存到空出的stake空間中(**pass parameters part_1**)
10.用*ldr* 將a(r2),b(r3) 從stake中取出使用(**pass parameters part_2**)
11.將a+b(add r3 r2)結果 存到r0
12.把sp移回原位 並跳回去原pc
3.把r0(pluse_fun 運算完的結果)存到r2(**return parameter part_1**)
4.把r2(pluse_fun 運算完的結果)存回c (**return parameter part_2**)
(*上面已經做完 c=pluse_fun(a,b)*)

5.取c放到r3
6.取a的位址到r2，並用 str r3,r2 來把c存到a
(*5,6為 a=c;*)

![圖片參考名稱](https://github.com/Way0405/ESEmbedded_HW03/blob/master/IMG_0817.jpg "pic_embedded_hw3_1")
![圖片參考名稱](https://github.com/Way0405/ESEmbedded_HW03/blob/master/IMG_0818.jpg "pic_embedded_hw3_2")
![圖片參考名稱](https://github.com/Way0405/ESEmbedded_HW03/blob/master/IMG_0819.jpg "pic_embedded_hw3_3")
