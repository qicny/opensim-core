$CURR_DIR = (pwd)

New-Item -Path . -Name build -ItemType Directory -Force | Out-Null

if(! $USE_CACHE) {
  Write-Host "---- Not downloading cache. Caching disabled."
  return
}

if($env:APPVEYOR_REPO_BRANCH -eq "master") {
  Write-Host "---- Not downloading cache. This is master build."
  return
}

if($env:APPVEYOR_REPO_COMMIT_MESSAGE -match "\[make clean\]") { 
  Write-Host "---- Not downloading cache. Make clean." 
  return
}

Write-Host '---- Checking for availability of cached build directory on Bintray.'
if($env:CMAKE_GENERATOR -like "*Win64") {
  $COMPILER = "msvc_win64"  
} else {
  $COMPILER = "msvc_win32"
}
$PACKAGE_NAME = $env:Platform + "_" + $COMPILER + "_" + "Release"

Write-Host "source dir: " + $env:OPENSIM_SOURCE_DIR
Set-Location $env:OPENSIM_SOURCE_DIR
$BRANCHTIP = $env:APPVEYOR_REPO_COMMIT
git fetch --quiet --unshallow
git fetch --quiet origin master:master
$BRANCHBASE = (git merge-base master $BRANCHTIP)

Write-Host $BRANCHBASE
Write-Host $PACKAGE_NAME

Write-Host $env:APPVEYOR_PULL_REQUEST_NUMBER
Write-Host $env:APPVEYOR_REPO_BRANCH
Write-Host $env:APPVEYOR_REPO_COMMIT
Write-Host $env:APPVEYOR_REPO_COMMIT_MESSAGE
Write-Host $env:Platform
Write-Host $env:Configuration