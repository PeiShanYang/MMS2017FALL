# MMS2017FALL/Assignment1
彩色圖片->灰階->黑白

##  作業內容簡介
<ol>
    <li>Write a program to read image</li>
    <li>Convert color images to gray-level images</li>
    <li>Implement the dithering algorithm</li>
</ol>

##  結果討論與比較

* Original Image

![Picture](000.jpg)

* Convert color images to gray-level images

  三通道的彩色圖片中的各通道的數值相加除以三，將此數值存入灰階圖片中的單通道。
  
![Picture](001.jpg)
  
* Implement the dithering algorithm

  一般的Dithering，將原本每像素增加為四個像素，圖片會變成四倍大。依照每個像素灰階的程度不同，打點的個數不同。
   我的打點方法：
  

矩陣|第0格|第1格|第2格|第3格
:---:|:---:|:---:|:---:|:---:
方位|左上|右上|左下|右下
255~201|255|255|255|255
200~151|0|255|255|255
150~101|0|255|255|0
100~51|0|0|255|0
50~0|0|0|0|0

![Picture](003.jpg)


  利用特殊演算法進行Dither Matrix運算的Dithering，不會造成圖片放大，但我覺得效果比放大四倍的差。
  
  範例Dither Matrix：
<table>
        <tr>
            <th>0</th>
            <th>8</th>
            <th>2</th>
            <th>10</th>
        </tr>
        <tr>
            <th>12</th>
            <th>4</th>
            <th>14</th>
            <th>6</th>
        </tr>
        <tr>
            <th>3</th>
            <th>11</th>
            <th>1</th>
            <th>9</th>
        </tr>
        <tr>
            <th>15</th>
            <th>7</th>
            <th>13</th>
            <th>5</th>
        </tr>
    </table>

![Picture](002.jpg)

  行列相反Dither Matrix：
<table>
        <tr>
            <th>0</th>
            <th>12</th>
            <th>3</th>
            <th>15</th>
        </tr>
        <tr>
            <th>8</th>
            <th>4</th>
            <th>11</th>
            <th>7</th>
        </tr>
        <tr>
            <th>2</th>
            <th>14</th>
            <th>1</th>
            <th>13</th>
        </tr>
        <tr>
            <th>10</th>
            <th>6</th>
            <th>9</th>
            <th>5</th>
        </tr>
    </table>
    
![Picture](004.jpg)

  直接輸入0~15的Dither Matrix：
<table>
        <tr>
            <th>0</th>
            <th>1</th>
            <th>2</th>
            <th>3</th>
        </tr>
        <tr>
            <th>4</th>
            <th>5</th>
            <th>6</th>
            <th>7</th>
        </tr>
        <tr>
            <th>8</th>
            <th>9</th>
            <th>10</th>
            <th>11</th>
        </tr>
        <tr>
            <th>12</th>
            <th>13</th>
            <th>14</th>
            <th>15</th>
        </tr>
    </table>
    
![Picture](005.jpg)

  大數字集中於中間其他平均分散的Dither Matrix：
<table>
        <tr>
            <th>0</th>
            <th>7</th>
            <th>5</th>
            <th>2</th>
        </tr>
        <tr>
            <th>8</th>
            <th>15</th>
            <th>13</th>
            <th>10</th>
        </tr>
        <tr>
            <th>11</th>
            <th>12</th>
            <th>14</th>
            <th>9</th>
        </tr>
        <tr>
            <th>3</th>
            <th>4</th>
            <th>6</th>
            <th>1</th>
        </tr>
    </table>
    
![Picture](006.jpg)

##  學習成果與收穫
* 灰階圖片使用單通道

  起初我將彩色圖片轉灰階的圖片基礎直接clone彩色圖片的，如此灰階圖片將有三通道，但事實上只有存一種數值，因此我將它改成了單通道，就不會多使用空間了。

* 灰階轉換方法
  * 平均法：Gray = (Red + Green + Blue) / 3
  * 基於人類感知：Gray = (Red * 0.299 + Green * 0.587 + Blue * 0.114)
  * 取單一通道

  上網搜尋了一些不同的灰階轉換方法。

方法|平均法|基於人類感知|取單一通道
:---:|:---:|:---:|:---:
優|算法簡單|有權重分別|用法簡單
缺|陰影及亮度不夠好|人類眼睛並非以這三色感受度最強|難預測轉換結果
