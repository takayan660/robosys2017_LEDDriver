# robosys2017_LEDDriver
Raspberry Pi3上で表示したい数字(0~9)を入力するとそれが7セグメントLEDに表示される

## Install
[デバイスドライバを作る](https://github.com/ryuichiueda/robosys2017/blob/master/05.md#%E3%83%87%E3%83%90%E3%82%A4%E3%82%B9%E3%83%89%E3%83%A9%E3%82%A4%E3%83%90%E3%82%92%E4%BD%9C%E3%82%8B)

上記のリンクに書いてある通りに再構築を行う。

次に以下を実行する

```bash
$ git clone https://github.com/takayan660/robosys2017_LEDDriver.git
$ cd robosys2017_LEDDriver
$ ./install.sh
```

## Pin
![](https://upload.wikimedia.org/wikipedia/commons/thumb/0/02/7_segment_display_labeled.svg/300px-7_segment_display_labeled.svg.png)

https://en.wikipedia.org/wiki/Seven-segment_display より

| Raspberry Pi3 GPIO  | Seven-segment display |
|:-------------------:|:---------------------:|
| 5                   | E                     |
| 6                   | D                     |
| 13                  | C                     |
| 19                  | G                     |
| 20                  | A                     |
| 21                  | B                     |
| 26                  | F                     |

## Execution
Inputには表示したい数字を入れる
```bash
$ cd robosys2017_LEDDriver
$ ./run ${Input}
```
| Input | Details                                 |
|:-----:|:----------------------------------------|
| c     | Display clear                           |
| 0 - 9 | Display numbers entered on the display  |
| r     | 0 - 9 dice                              |

## Demo
https://youtu.be/5dKZrvqSnIA

[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/5dKZrvqSnIA/0.jpg)](http://www.youtube.com/watch?v=5dKZrvqSnIA)
