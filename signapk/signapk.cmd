copy ..\bin\TVActivity-ocas-dvbc.apk .
java -jar signapk.jar platform.x509.pem platform.pk8 TVActivity-ocas-dvbc.apk signed.apk
