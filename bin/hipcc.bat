@IF DEFINED HIP_PATH (set HIPCC="%HIP_PATH%/bin/hipcc") ELSE (set HIPCC="%CD%/hipcc")
@perl %HIPCC% %*
