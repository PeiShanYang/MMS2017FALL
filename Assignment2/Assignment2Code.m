% amplitude
A = 1

% Table level 2 and 4
Freq2 = [65 73 82 87 98 110 124]
Freq4 = [262 294 330 349 392 440 494]

fs = 8000
T2 = (0 : fs) / fs
T4 = (0 : 0.5 * fs) / fs

% 1/2 notes
AltoDo2 = A * sin(2 * pi * Freq4(1) * T2)
AltoRe2 = A * sin(2 * pi * Freq4(2) * T2)
AltoMi2 = A * sin(2 * pi * Freq4(3) * T2)
AltoFa2 = A * sin(2 * pi * Freq4(4) * T2)
AltoSol2 = A * sin(2 * pi * Freq4(5) * T2)
AltoLa2 = A * sin(2 * pi * Freq4(6) * T2)
AltoSi2 = A * sin(2 * pi * Freq4(7) * T2)

% 1/4 notes
BassoDo4 = A * sin(2 * pi * Freq2(1) * T4)
BassoRe4 = A * sin(2 * pi * Freq2(2) * T4)
BassoMi4 = A * sin(2 * pi * Freq2(3) * T4)
BassoFa4 = A * sin(2 * pi * Freq2(4) * T4)
BassoSol4 = A * sin(2 * pi * Freq2(5) * T4)
BassoLa4 = A * sin(2 * pi * Freq2(6) * T4)
BassoSi4 = A * sin(2 * pi * Freq2(7) * T4)
AltoDo4 = A * sin(2 * pi * Freq4(1) * T4)
AltoRe4 = A * sin(2 * pi * Freq4(2) * T4)
AltoMi4 = A * sin(2 * pi * Freq4(3) * T4)
AltoFa4 = A * sin(2 * pi * Freq4(4) * T4)
AltoSol4 = A * sin(2 * pi * Freq4(5) * T4)
AltoLa4 = A * sin(2 * pi * Freq4(6) * T4)
AltoSi4 = A * sin(2 * pi * Freq4(7) * T4)

% 主旋律與伴奏
Front = [AltoSol4 AltoMi4 AltoMi2 0 AltoFa4 AltoRe4 AltoRe2 0 AltoDo4 AltoRe4 AltoMi4 AltoFa4 AltoSol4 AltoSol4 AltoSol2 0]
Back = [BassoMi4 BassoSol4 BassoRe4 BassoSol4 BassoDo4 BassoRe4 BassoMi4 BassoDo4 BassoDo4 BassoRe4 BassoMi4 BassoFa4 BassoMi4 BassoRe4 BassoDo4 BassoSol4]

% 融合
Song = Front + Back

% 播放
sound(Song)
