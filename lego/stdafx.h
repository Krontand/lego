// stdafx.h: включаемый файл для стандартных системных включаемых файлов
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
//

#pragma once

#define _USE_MATH_DEFINES

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows:
#include <windows.h>

// Файлы заголовков C RunTime
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


#include <CommCtrl.h>
#include <commdlg.h>
#include <Shlobj.h>
#pragma comment(lib,"Comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


// TODO: Установите здесь ссылки на дополнительные заголовки, требующиеся для программы
#include "Resource.h"
#include <vector>
#include <math.h>
#include <cmath>
#include <time.h>
#include <omp.h>

#define BTN_OK 888
#define TXT_LEGO 889
#define TXT_DESIGNER 890
#define EDIT_X 891
#define EDIT_Y 892
#define EDIT_Z 893
#define TXT_COLOR 894
#define RCT_COLOR 895
#define BTN_CHCOLOR 896
#define RCT_SEPARATE 897
#define CB_CHOOSEBRICK 898
#define CB_CHOOSEACTIVE	899
#define TXT_MODORDELETE 900
#define BTN_DELETE 901
