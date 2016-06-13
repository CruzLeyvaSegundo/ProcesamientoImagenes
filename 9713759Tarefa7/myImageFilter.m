function [img]=myImageFilter(img0,h)
X=img0;
siz=size(X);
row_zeros=zeros(1,siz(2));
X=[row_zeros;X;row_zeros];
colum_zeros=zeros(siz(1)+2,1);
X=[colum_zeros X colum_zeros];
X(1,:)=X(2,:);
X(end,:)=X(end-1,:);
X(:,1)=X(:,2);
X(:,end)=X(:,end-1);
X=single(X);
for i=2:(siz(1)+1)
    for j=2:(siz(2)+1)
        %making a 3X3 matrix
        addi=0;
        T=[X(i-1,j-1) X(i-1,j) X(i-1,j+1);X(i,j-1) X(i,j) X(i,j+1);X(i+1,j-1) X(i+1,j) X(i+1,j+1)]; 
        
        
        for k=1:3
            for l=1:3
                addi=(addi+T(k,l)*h(4-k,4-l));
            end
        end
        img(i-1,j-1)=addi;
    end  
    
end