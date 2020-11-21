@echo off
SET g=Global
ECHO;%g%	

SETLOCAL
	SET l=Local
	ECHO;%l%
REM // ローカル変数をグローバル変数に代入します。
ENDLOCAL & SET g=%l%

ECHO;%g%
SET g=