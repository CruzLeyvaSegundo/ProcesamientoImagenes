img_RGB = imread('.\ajedrez.png');
img_gray=rgb2gray(img_RGB);
img_double=im2double(img_gray);
%Detectores de lineas horizontales y verticales
h=[-1 -1 -1;
    2  2  2;
   -1 -1 -1];
v=[-1  2 -1;
   -1  2 -1;
   -1  2 -1];

%Obtencion de las lineas verdes y 4 lineas rojas horizontales
r1_filtro=medfilt2(img_double,[3 3]);
r1_bodeVertical=imfilter(r1_filtro,h,'replicate');
r1_abs=abs(r1_bodeVertical);
r1=r1_abs>=(max(r1_abs(:))-1.9);

%Obtencion de las lineas azules y 3 lineas rojas verticales
r2_filtro=medfilt2(img_double,[3 3]);
r1_bodeHorizontal=imfilter(r2_filtro,v,'replicate');
r2_abs=abs(r1_bodeHorizontal);
r2=r2_abs>=(max(r2_abs(:))-1.74);

%Obtencion de 1 linea roja horizontal
r3_filtro=medfilt2(img_double,[5 5]);
r3_bodeHorizontal=edge(r3_filtro,'zerocross');
r3=imfilter(r3_bodeHorizontal,h,'replicate');

%Obtencion de 1 linea roja vertical
gauss=fspecial('gaussian',[5 5],0.67);
r4_filtro=imfilter(img_double,gauss,'replicate');
r4_bodeVertical=edge(r4_filtro,'canny');
r4=imfilter(r4_bodeVertical,v,'replicate');

figure,subplot(2,1,1),imshow(r1),title('lineas verdes + 4 lineas rojas horizontales');
subplot(2,1,2), imshow(r2),title('lineas azules + 3 lineas rojas verticales');
figure,subplot(2,1,1), imshow(r3),title('1 linea horizontal');
subplot(2,1,2), imshow(r4),title('1 linea vertical');
figure, imshow(img_RGB);

%%%%%%%%%%%%%%%DIBUJO DE LAS LINEAS OBTENIDAS %%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%LINEAS VERDES + 4 LINEAS ROJAS HORIZAONTALES%%%%%%%%%%%%
[H,T,R] = goHough(r1,'Hough lineas verdes + 4 lineas rojas horizontales');
%imshow(H,[],'XData',T,'YData',R,...
 %           'InitialMagnification','fit');
xlabel('\theta'), ylabel('\rho');
axis on, axis normal, hold on;
P  = houghpeaks(H,40,'threshold',ceil(0.45*max(H(:))));
lines = houghlines(r1,T,R,P,'FillGap',40,'MinLength',100);
max_len = 0;
for k = 1:length(lines)
   xy = [lines(k).point1; lines(k).point2];
   % Plot beginnings and ends of lines
   if(xy(1,2)>100&&xy(1,2)<400)
       plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','green');
   else
       plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','red');
   end
   % Determine the endpoints of the longest line segment
   plot(xy(1,1),xy(1,2),'x','LineWidth',2,'Color','green');
   plot(xy(2,1),xy(2,2),'x','LineWidth',2,'Color','green');
   len = norm(lines(k).point1 - lines(k).point2);
   if ( len > max_len)
      max_len = len;
      xy_long = xy;
   end
end

%%%%%%%%%%%%%%%%%%%%%%%%%LINEAS AZULES Y 3 LINEAS ROJAS VERTICALES%%%%%%%%%%%%%%%%%%%%%%%%
[H,T,R] = goHough(r2,'Hough lineas azules + 3 lineas rojas verticales');
%imshow(H,[],'XData',T,'YData',R,...
 %           'InitialMagnification','fit');
xlabel('\theta'), ylabel('\rho');
axis on, axis normal, hold on;
P  = houghpeaks(H,100,'threshold',ceil(0.61*max(H(:))));
lines = houghlines(r2,T,R,P,'FillGap',45,'MinLength',100);
max_len = 0;
for k = 1:length(lines)
   xy = [lines(k).point1; lines(k).point2];
   % Plot beginnings and ends of lines
   if(xy(2,1)>100&&xy(2,1)<650)
       plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','blue');
   else
        plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','red');
   end
   % Determine the endpoints of the longest line segment
   plot(xy(1,1),xy(1,2),'x','LineWidth',2,'Color','blue');
   plot(xy(2,1),xy(2,2),'x','LineWidth',2,'Color','blue');
   len = norm(lines(k).point1 - lines(k).point2);
   if ( len > max_len)
      max_len = len;
      xy_long = xy;
   end
end

%%%%%%%%%%%%%%%%%%1 LINEA ROJA HORIZONTALE%%%%%%%%%%%%%%%
%r2=edge_canny;
[H,T,R] = goHough(r3,'Hough 1 linea roja horizontal');
%imshow(H,[],'XData',T,'YData',R,...
 %           'InitialMagnification','fit');
xlabel('\theta'), ylabel('\rho');
axis on, axis normal, hold on;
P  = houghpeaks(H,40,'threshold',ceil(0.45*max(H(:))));
lines = houghlines(r3,T,R,P,'FillGap',40,'MinLength',100);
max_len = 0;
for k = 1:length(lines)
   xy = [lines(k).point1; lines(k).point2];
   if(xy(1,2)<100&&xy(1,2)>80)
        % Plot beginnings and ends of lines
        plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','red');
        % Determine the endpoints of the longest line segment
        plot(xy(1,1),xy(1,2),'x','LineWidth',2,'Color','green');
        plot(xy(2,1),xy(2,2),'x','LineWidth',2,'Color','red');   
   end
   len = norm(lines(k).point1 - lines(k).point2);
   if ( len > max_len)
      max_len = len;
      xy_long = xy;
   end
end

%%%%%%%%%%%%%%%%%% 1 LINEA ROJA VERTICAL%%%%%%%%%%%%%%%
[H,T,R] = goHough(r4,'Hough 1 linea roja vertical');
%imshow(H,[],'XData',T,'YData',R,...
 %           'InitialMagnification','fit');
xlabel('\theta'), ylabel('\rho');
axis on, axis normal, hold on;
P  = houghpeaks(H,100,'threshold',ceil(0.61*max(H(:))));
lines = houghlines(r4,T,R,P,'FillGap',18,'MinLength',300);
max_len = 0;
for k = 1:length(lines)
   xy = [lines(k).point1; lines(k).point2];
   if(xy(2,1)>750)
        % Plot beginnings and ends of lines
        plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','red');
        % Determine the endpoints of the longest line segment       
        plot(xy(1,1),xy(1,2),'x','LineWidth',2,'Color','blue');
        plot(xy(2,1),xy(2,2),'x','LineWidth',2,'Color','red');   
   end
   len = norm(lines(k).point1 - lines(k).point2);
   if ( len > max_len)
      max_len = len;
      xy_long = xy;
   end
end