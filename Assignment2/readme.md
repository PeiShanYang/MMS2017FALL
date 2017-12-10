# MMS2017FALL/Assignment2
音訊處理

##  作業內容簡介
<ol><li>Tonal Sound Generation</li>
    <li>Frequency Modulation</li>
</ol>

##  結果討論與比較
因為GUI介面製作尚不熟悉的問題，只好將使用者輸入簡譜以及同時伴奏的功能分開製作。

* 使用者輸入簡譜可播放

![Picture](UserPlay.JPG)

在這裡使用者可以輸入自己想輸的音符，按下播放後即放出音樂。

* The format I design for the input text file of musical notes

使用者將輸入1-7代表level4的Do-Si、a-g代表level2的Do-Si，

在此程式中只有用到四分音符，所以轉換如下：

使用者輸入|程式中的命名||使用者輸入|程式中的命名
:---:|:---:|:---:|:---:|:---:
1|AltoDo4||a|BassoDo4
2|AltoRe4||b|BassoRe4
3|AltoMi4||c|BassoMi4
4|AltoFa4||d|BassoFa4
5|AltoSol4||e|BassoSol4
6|AltoLa4||f|BassoLa4
7|AltoSi4||g|BassoSi4

* The flowchart of User Playing Mode

![Picture](UserPlayFlowchart.JPG)

* The way to set up and run My program

這次使用Matlab來製作，首先先置備好level2及level4中的四分音符，

因不是要做作曲功能的程式，所以在這裡沒有做其他音符。

製成音符步驟如下：

