# ロボット動作用のプログラム

## 実行環境  
今回は、microSDカードにDebianを入れてプログラムを実行する予定。  
そのため、Windowsの場合は、Microsoft Store から WSLのOSとして  
Debian系の Ubunbu 18.04 をインストールして使うのが楽。  
  
下記 URL を参照して初期設定を済ませないと  
clang のインストールに**ものすごく時間がかかる**ため注意。  
http://www.aise.ics.saitama-u.ac.jp/~gotoh/HowToInstallUbuntu1804OnWSL.html  

## ビルド方法

1. programブランチにチェックアウト  

2. 下記のコマンドでclangをインストール  
```
sudo apt-get install clang++-6.0 -y  
```
3. cd コマンドを使ってprogramディレクトリへ移動  

4. 下記のコマンドでビルド  
```
make  
```
5. 下記のコマンドで実行  
```
./start  
```