# MMS2017FALL/Assignment1
彩色圖片->灰階->黑白

## 內容簡介
<ol>
    <li>Write a program to read image</li>
    <li>Convert color images to gray-level images</li>
    <li>Implement the dithering algorithm</li>
</ol>

##  結果討論
* 灰階圖片使用單通道
  * 起初我將彩色圖片轉灰階的圖片基礎直接clone彩色圖片的，如此灰階圖片將有三通道，但事實上只有存一種數值，因此我將它改成了單通道，就不會多使用空間了。
* 灰階轉換方法
  * 平均法：Gray = (Red + Green + Blue) / 3
  * 基於人類感知：Gray = (Red * 0.299 + Green * 0.587 + Blue * 0.114)
  * 取單一通道
