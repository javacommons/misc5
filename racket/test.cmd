@echo off
SET g=Global
ECHO;%g%	

SETLOCAL
	SET l=Local
	ECHO;%l%
REM // ���[�J���ϐ����O���[�o���ϐ��ɑ�����܂��B
ENDLOCAL & SET g=%l%

ECHO;%g%
SET g=