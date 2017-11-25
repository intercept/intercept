# Create host addon folders and copy items
New-Item $env:APPVEYOR_BUILD_FOLDER\artifacts\@intercept\addons -type directory
Copy-Item $env:APPVEYOR_BUILD_FOLDER\build\win32\intercept\RelWithDebInfo\intercept.dll $env:APPVEYOR_BUILD_FOLDER\artifacts\@intercept
Copy-Item $env:APPVEYOR_BUILD_FOLDER\build\win64\intercept\RelWithDebInfo\intercept_x64.dll $env:APPVEYOR_BUILD_FOLDER\artifacts\@intercept

# Create dev folders and copy items
New-Item $env:APPVEYOR_BUILD_FOLDER\artifacts\intercept\client\include -type directory
Copy-Item $env:APPVEYOR_BUILD_FOLDER\src\client\headers\* $env:APPVEYOR_BUILD_FOLDER\artifacts\intercept\client\include -recurse

New-Item $env:APPVEYOR_BUILD_FOLDER\artifacts\intercept\client\lib -type directory
Copy-Item $env:APPVEYOR_BUILD_FOLDER\build\win32\intercept_client\RelWithDebInfo\intercept_client.lib $env:APPVEYOR_BUILD_FOLDER\artifacts\intercept\client\lib

New-Item $env:APPVEYOR_BUILD_FOLDER\artifacts\intercept\client\lib64 -type directory
Copy-Item $env:APPVEYOR_BUILD_FOLDER\build\win64\intercept_client\RelWithDebInfo\intercept_client.lib $env:APPVEYOR_BUILD_FOLDER\artifacts\intercept\client\lib64

New-Item $env:APPVEYOR_BUILD_FOLDER\artifacts\intercept\host\@intercept\addons -type directory
Copy-Item $env:APPVEYOR_BUILD_FOLDER\build\win32\intercept\RelWithDebInfo\intercept.dll $env:APPVEYOR_BUILD_FOLDER\artifacts\intercept\host\@intercept
Copy-Item $env:APPVEYOR_BUILD_FOLDER\build\win32\intercept\RelWithDebInfo\intercept.pdb $env:APPVEYOR_BUILD_FOLDER\artifacts\intercept\host\@intercept
Copy-Item $env:APPVEYOR_BUILD_FOLDER\build\win64\intercept\RelWithDebInfo\intercept_x64.dll $env:APPVEYOR_BUILD_FOLDER\artifacts\intercept\host\@intercept
Copy-Item $env:APPVEYOR_BUILD_FOLDER\build\win64\intercept\RelWithDebInfo\intercept_x64.pdb $env:APPVEYOR_BUILD_FOLDER\artifacts\intercept\host\@intercept

# Pack host addon
Start-Process -FilePath "$env:APPVEYOR_BUILD_FOLDER\tools\armake_w64.exe" -ArgumentList "build `"$env:APPVEYOR_BUILD_FOLDER\rv\addons\core`" `"$env:APPVEYOR_BUILD_FOLDER\artifacts\intercept\intercept_host.pbo`""

# Copy host addon to host addon folder
Copy-Item $env:APPVEYOR_BUILD_FOLDER\artifacts\intercept\intercept_host.pbo $env:APPVEYOR_BUILD_FOLDER\artifacts\@intercept\addons

# Define zip extension when commit tag is present
$zipExtension = ""
if($env:APPVEYOR_REPO_TAG) {
    $zipExtension = "_$env:APPVEYOR_REPO_TAG_NAME"
}

# Zip host artifact and publish it
7z a "$env:APPVEYOR_BUILD_FOLDER\artifacts\intercept_host$zipExtension.zip" "$env:APPVEYOR_BUILD_FOLDER\artifacts\@intercept"
Push-AppveyorArtifact "$env:APPVEYOR_BUILD_FOLDER\artifacts\intercept_host$zipExtension.zip"  

# Zip dev artifact and publish it
7z a "$env:APPVEYOR_BUILD_FOLDER\artifacts\intercept_dev$zipExtension.zip" "$env:APPVEYOR_BUILD_FOLDER\artifacts\intercept"
Push-AppveyorArtifact "$env:APPVEYOR_BUILD_FOLDER\artifacts\intercept_dev$zipExtension.zip"  