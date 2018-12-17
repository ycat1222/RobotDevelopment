# ロボット動作用のプログラム

## 実行環境  
今回は、microSDカードにDebianを入れてプログラムを実行する予定。  
そのため、Windowsの場合は、Microsoft Store から WSLのOSとして  
Debian系の Ubunbu 18.04 をインストールして使うのが楽。  
  
下記 URL を参照して初期設定を済ませないと  
clang のインストールに**ものすごく時間がかかる**ため注意。  
http://www.aise.ics.saitama-u.ac.jp/~gotoh/HowToInstallUbuntu1804OnWSL.html  

## ビルド方法

1. 下記のコマンドでclangをインストール  
```
sudo apt-get install clang++-6.0 -y  
```
2. cd コマンドを使ってprogramディレクトリへ移動  

3. 下記のコマンドでビルド  
```
make  
```
4. 下記のコマンドで実行  
```
./start  
```

## モータドライバボードでのPWMの扱いについて  

|  モータドライバ | P9_ピン番号:PWM | IN1:GPIO番号 | IN2:GPIO番号 |
|:----:|:----:|:----:|:----:|
|No.1|P9_14|61|60|
|No.2|P9_22|65|46|

|  IN1 | IN2 | 出力 | 
|:----:|:----:|:----:|
|1|1|ブレーキ|
|0|1|逆転(正転)|
|1|0|正転(逆転)|
|0|0|ストップ|
