include_directories("." "AES/")
include_directories("." "CommonHeader/")
include_directories("." "FileOperation/")
include_directories("." "GridCtrl_src/")
include_directories("." "res/")
add_definitions(-D_AFXDLL)	
set(CMAKE_MFC_FLAG 1) 

set(aes
    AES/AES.h
    AES/AES.cpp
    )

set(fileopr
    FileOperation/FileOperation.h
    FileOperation/FileOperation.cpp
    )

set(comhd
    CommonHeader/CommonDef.h
    )   

set(grid
    GridCtrl_src/CellRange.h
    GridCtrl_src/GridCell.cpp
    GridCtrl_src/GridCell.h
    GridCtrl_src/GridCellBase.cpp
    GridCtrl_src/GridCellBase.h
    GridCtrl_src/GridCellProvider.cpp
    GridCtrl_src/GridCellProvider.h
    GridCtrl_src/GridCtrl.cpp
    GridCtrl_src/GridCtrl.h
    GridCtrl_src/GridCtrlProvider.cpp
    GridCtrl_src/GridCtrlProvider.h
    GridCtrl_src/GridDropTarget.cpp
    GridCtrl_src/GridDropTarget.h
    GridCtrl_src/GridItems.cpp
    GridCtrl_src/GridItems.h
    GridCtrl_src/GridItemsProvider.cpp
    GridCtrl_src/GridItemsProvider.h
    GridCtrl_src/InPlaceEdit.cpp
    GridCtrl_src/InPlaceEdit.h
    GridCtrl_src/MemDC.h
    GridCtrl_src/TitleTip.cpp
    GridCtrl_src/TitleTip.h
    )
    
set (resources
    DeskToolsAssemble.rc
    )
   	
source_group(AES FILES ${aes})    
source_group(FileOperation FILES ${fileopr})    
source_group(CommonHeader FILES ${comhd})     
source_group(GridCtrl_src FILES ${grid})     
source_group(Resources FILES ${resources})    

set(HeadFiles
    resource.h
    stdafx.h
    targetver.h
    stdafx.cpp    
    )
        
set(cfgdlg
	ConfigDlg.h
	ConfigDlg.cpp
	)
		    
set(DeskToolsAssemble 
	DeskToolsAssemble.h
	DeskToolsAssemble.cpp
	)
	
set(DeskToolsAssembleDlg
	DeskToolsAssembleDlg.h
	DeskToolsAssembleDlg.cpp
	)

set(ConfigDlg
	ConfigDlg.h
	ConfigDlg.cpp
	)	
	
add_executable(DTA WIN32 
	${DeskToolsAssemble} 
	${DeskToolsAssembleDlg}
	${HeadFiles}
	${aes}
	${fileopr}
	${comhd}
	${grid}
	${resources}
	${ConfigDlg}
	)

#target_link_libraries(GetWindowPixel psapi.lib)		

set_target_properties(DTA PROPERTIES
    COMPILE_DEFINITIONS _AFXDLL,_BIND_TO_CURRENT_CRT_VERSION,_BIND_TO_CURRENT_MFC_VERSION
    )	