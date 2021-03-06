// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <wrl.h>
#include <windows.h>
#include <dxgi1_4.h>
#include <d3d11_3.h>
#include <d2d1_3.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <d2d1effects_2.h>
#include <dwrite_3.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <wincodec.h>
#include <Wincodecsdk.h>

#include <stdio.h>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <mutex>
#include <condition_variable>
#include <filesystem>

#include "..\common\inc\errors.h"
#include "..\common\inc\application.h"
#include "..\common\inc\concurrentqueue.h"
#include "..\common\inc\device_resources.h"

#include "dicom_file.h"
#include "dicom_image_helper.h"
#include "file_helpers.h"
#include "operation.h"

