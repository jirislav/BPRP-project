echoudp('on',4012)
u = udp('127.0.0.1',4012);
u.Timeout=10
fopen(u)

fwrite(u,65:74)
A = fread(u,10);

echoudp('off')
fclose(u)