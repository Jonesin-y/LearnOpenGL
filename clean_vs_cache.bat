@echo off
echo ============================================
echo   Cleaning VS Cache Files
echo ============================================
echo.

set PROJECT_DIR=%~dp0

echo [1/3] Removing .vs folder (IntelliSense / Browse / Copilot cache)...
if exist "%PROJECT_DIR%.vs" (
    rmdir /s /q "%PROJECT_DIR%.vs" 2>nul
    if exist "%PROJECT_DIR%.vs" (
        echo   FAILED: .vs is still locked. Please close Visual Studio completely!
        goto :end
    )
    echo   Done. .vs removed.
) else (
    echo   .vs not found, skipping.
)

echo.
echo [2/3] Removing bin/ (output binaries)...
if exist "%PROJECT_DIR%bin" (
    rmdir /s /q "%PROJECT_DIR%bin"
    echo   Done. bin removed.
) else (
    echo   bin not found, skipping.
)

echo.
echo [3/3] Removing bin-int/ (intermediate build files)...
if exist "%PROJECT_DIR%bin-int" (
    rmdir /s /q "%PROJECT_DIR%bin-int"
    echo   Done. bin-int removed.
) else (
    echo   bin-int not found, skipping.
)

echo.
echo ============================================
echo   Cleanup complete!
echo   Reopen the solution in Visual Studio and
echo   rebuild (Ctrl+Shift+B). VS will regenerate
echo   all caches from scratch.
echo ============================================

:end
pause
