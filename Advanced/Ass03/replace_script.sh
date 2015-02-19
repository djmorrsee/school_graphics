egrep -lRZ "\"dj.h\"" . | xargs -0 -l sed -i -e "s,dj.h,../dj.h,"
