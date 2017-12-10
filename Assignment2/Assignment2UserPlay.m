function varargout = Assignment2UserPlay(varargin)
% ASSIGNMENT2USERPLAY M-file for Assignment2UserPlay.fig
%      ASSIGNMENT2USERPLAY, by itself, creates a new ASSIGNMENT2USERPLAY or raises the existing
%      singleton*.
%
%      H = ASSIGNMENT2USERPLAY returns the handle to a new ASSIGNMENT2USERPLAY or the handle to
%      the existing singleton*.
%
%      ASSIGNMENT2USERPLAY('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in ASSIGNMENT2USERPLAY.M with the given input arguments.
%
%      ASSIGNMENT2USERPLAY('Property','Value',...) creates a new ASSIGNMENT2USERPLAY or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Assignment2UserPlay_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Assignment2UserPlay_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Assignment2UserPlay

% Last Modified by GUIDE v2.5 11-Dec-2017 03:19:15

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Assignment2UserPlay_OpeningFcn, ...
                   'gui_OutputFcn',  @Assignment2UserPlay_OutputFcn, ...
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


% --- Executes just before Assignment2UserPlay is made visible.
function Assignment2UserPlay_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Assignment2UserPlay (see VARARGIN)

% Choose default command line output for Assignment2UserPlay
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Assignment2UserPlay wait for user response (see UIRESUME)
% uiwait(handles.figure1);

% --- Outputs from this function are returned to the command line.
function varargout = Assignment2UserPlay_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function edit2_Callback(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit2 as text
%        str2double(get(hObject,'String')) returns contents of edit2 as a double


% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% ªì©l¤Æ

% amplitude
A = 1;

% Table level 2 and 4
Freq2 = [65 73 82 87 98 110 124];
Freq4 = [262 294 330 349 392 440 494];

fs = 8000;
T4 = (1 : 0.25 * fs) / fs;

% 1/4 notes
Zero4 = A * sin(2 * pi * 0 * T4);
BassoDo4 = A * sin(2 * pi * Freq2(1) * T4);
BassoRe4 = A * sin(2 * pi * Freq2(2) * T4);
BassoMi4 = A * sin(2 * pi * Freq2(3) * T4);
BassoFa4 = A * sin(2 * pi * Freq2(4) * T4);
BassoSol4 = A * sin(2 * pi * Freq2(5) * T4);
BassoLa4 = A * sin(2 * pi * Freq2(6) * T4);
BassoSi4 = A * sin(2 * pi * Freq2(7) * T4);
AltoDo4 = A * sin(2 * pi * Freq4(1) * T4);
AltoRe4 = A * sin(2 * pi * Freq4(2) * T4);
AltoMi4 = A * sin(2 * pi * Freq4(3) * T4);
AltoFa4 = A * sin(2 * pi * Freq4(4) * T4);
AltoSol4 = A * sin(2 * pi * Freq4(5) * T4);
AltoLa4 = A * sin(2 * pi * Freq4(6) * T4);
AltoSi4 = A * sin(2 * pi * Freq4(7) * T4);
textString = get(handles.edit2,'String');
len = length(textString);

for i = 1:len
	switch textString(i)
        case '0'
            sound(Zero4);
		case '1'
            sound(AltoDo4);
		case '2'
			sound(AltoRe4);
		case '3'
			sound(AltoMi4);
		case '4'
			sound(AltoFa4);
        case '5'
            sound(AltoSol4);
        case '6'
            sound(AltoLa4);
        case '7'
            sound(AltoSi4);
        case 'a'
            sound(BassoDo4);
		case 'b'
			sound(BassoRe4);
		case 'c'
			sound(BassoMi4);
		case 'd'
			sound(BassoFa4);
        case 'e'
            sound(BassoSol4);
        case 'f'
            sound(BassoLa4);
        case 'g'
            sound(BassoSi4);
    end
end


