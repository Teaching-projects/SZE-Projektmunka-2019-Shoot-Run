cd %cd%\Headers
odb --profile qt --std c++11 -d mysql --generate-schema --generate-query --generate-session event.h image.h track.h tardis.h user.h
pause