# build.ps1

# Stop on any errors
$ErrorActionPreference = "Stop"

# Project root (script should be in project root)
$PROJECT_ROOT = Split-Path -Parent $MyInvocation.MyCommand.Path

# Create build directory if it doesn't exist
$BUILD_DIR = Join-Path $PROJECT_ROOT "build"
if (-Not (Test-Path $BUILD_DIR)) {
    New-Item -ItemType Directory -Path $BUILD_DIR | Out-Null
}

# Go to build directory
Set-Location $BUILD_DIR

# Generate build files using CMake
cmake ..

# Build the project
cmake --build .

# Run the executable
$EXECUTABLE = Join-Path $BUILD_DIR "Lab.exe"
if (Test-Path $EXECUTABLE) {
    Write-Host "Running $EXECUTABLE..."

    # Optional: Set CPU affinity (e.g., cores 0-3)
    $process = Start-Process -FilePath $EXECUTABLE -PassThru
    # CPU affinity mask: cores 0-3 = 0b1111 = 15
    $process.ProcessorAffinity = 15
    $process.WaitForExit()
} else {
    Write-Host "Error: Executable $EXECUTABLE not found!"
    exit 1
}
