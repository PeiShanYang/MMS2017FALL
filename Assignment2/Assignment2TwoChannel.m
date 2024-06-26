function varargout = Assignment2TwoChannel(varargin)
% ASSIGNMENT2TWOCHANNEL M-file for Assignment2TwoChannel.fig
%      ASSIGNMENT2TWOCHANNEL, by itself, creates a new ASSIGNMENT2TWOCHANNEL or raises the existing
%      singleton*.
%
%      H = ASSIGNMENT2TWOCHANNEL returns the handle to a new ASSIGNMENT2TWOCHANNEL or the handle to
%      the existing singleton*.
%
%      ASSIGNMENT2TWOCHANNEL('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in ASSIGNMENT2TWOCHANNEL.M with the given input arguments.
%
%      ASSIGNMENT2TWOCHANNEL('Property','Value',...) creates a new ASSIGNMENT2TWOCHANNEL or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Assignment2TwoChannel_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Assignment2TwoChannel_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Assignment2TwoChannel

% Last Modified by GUIDE v2.5 11-Dec-2017 03:59:09

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Assignment2TwoChannel_OpeningFcn, ...
                   'gui_OutputFcn',  @Assignment2TwoChannel_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before Assignment2TwoChannel is made visible.
function Assignment2TwoChannel_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Assignment2TwoChannel (see VARARGIN)

% Choose default command line output for Assignment2TwoChannel
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Assignment2TwoChannel wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Assignment2TwoChannel_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% amplitude
A = 1

% Table level 4
Freq4 = [262 294 330 349 392 440 494]

fs = 8000
T2 = (0 : 0.5 * fs) / fs
T4 = (0 : 0.25 * fs) / fs

% 1/2 notes
AltoDo2 = A * sin(2 * pi * Freq4(1) * T2)
AltoRe2 = A * sin(2 * pi * Freq4(2) * T2)
AltoMi2 = A * sin(2 * pi * Freq4(3) * T2)
AltoFa2 = A * sin(2 * pi * Freq4(4) * T2)
AltoSol2 = A * sin(2 * pi * Freq4(5) * T2)
AltoLa2 = A * sin(2 * pi * Freq4(6) * T2)
AltoSi2 = A * sin(2 * pi * Freq4(7) * T2)

% 1/4 notes
AltoDo4 = A * sin(2 * pi * Freq4(1) * T4)
AltoRe4 = A * sin(2 * pi * Freq4(2) * T4)
AltoMi4 = A * sin(2 * pi * Freq4(3) * T4)
AltoFa4 = A * sin(2 * pi * Freq4(4) * T4)
AltoSol4 = A * sin(2 * pi * Freq4(5) * T4)
AltoLa4 = A * sin(2 * pi * Freq4(6) * T4)
AltoSi4 = A * sin(2 * pi * Freq4(7) * T4)

% �D�۫�
Front = [AltoSol4 AltoMi4 AltoMi2 0 AltoFa4 AltoRe4 AltoRe2 0 AltoDo4 AltoRe4 AltoMi4 AltoFa4 AltoSol4 AltoSol4 AltoSol2 0]

% ����
sound(Front, fs)


% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% amplitude
A = 1

% Table level 2
Freq2 = [65 73 82 87 98 110 124]

fs = 8000
T4 = (0 : 0.25 * fs) / fs

% 1/4 notes
BassoDo4 = A * sin(2 * pi * Freq2(1) * T4)
BassoRe4 = A * sin(2 * pi * Freq2(2) * T4)
BassoMi4 = A * sin(2 * pi * Freq2(3) * T4)
BassoFa4 = A * sin(2 * pi * Freq2(4) * T4)
BassoSol4 = A * sin(2 * pi * Freq2(5) * T4)
BassoLa4 = A * sin(2 * pi * Freq2(6) * T4)
BassoSi4 = A * sin(2 * pi * Freq2(7) * T4)

% ��
Back = [BassoMi4 BassoSol4 BassoRe4 BassoSol4 BassoDo4 BassoRe4 BassoMi4 BassoDo4 BassoDo4 BassoRe4 BassoMi4 BassoFa4 BassoMi4 BassoRe4 BassoDo4 BassoSol4]

% ����
sound(Back, fs)


% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% amplitude
A = 1

% Table level 2 and 4
Freq2 = [65 73 82 87 98 110 124]
Freq4 = [262 294 330 349 392 440 494]

fs = 8000
T2 = (0 : 0.5 * fs) / fs
T4 = (0 : 0.25 * fs) / fs

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

% �D�۫߻P��
Front = [AltoSol4 AltoMi4 AltoMi2 0 AltoFa4 AltoRe4 AltoRe2 0 AltoDo4 AltoRe4 AltoMi4 AltoFa4 AltoSol4 AltoSol4 AltoSol2 0]
Back = [BassoMi4 BassoSol4 BassoRe4 BassoSol4 BassoDo4 BassoRe4 BassoMi4 BassoDo4 BassoDo4 BassoRe4 BassoMi4 BassoFa4 BassoMi4 BassoRe4 BassoDo4 BassoSol4]

% �ĦX
Song = Front + Back

% ����
sound(Song, fs)

