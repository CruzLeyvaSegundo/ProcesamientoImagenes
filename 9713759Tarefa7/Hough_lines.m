function [H, thetas, rhos, expected_average_H_for_uniform_edge_distribution] = ...
    Hough_lines(gradientImY, gradientImX, rhoSpacing, thetaSpacing)

assert(rhoSpacing>0);
assert(thetaSpacing>0);
assert(thetaSpacing<pi/2);

Y= size(gradientImY,1);
assert(Y==size(gradientImX,1));
X= size(gradientImY,2);
assert(X==size(gradientImX,2));

maxRho= norm([Y X],2);
assert(rhoSpacing<maxRho/2);
% The minimum is min_theta(-sin(theta) Y) which is -Y
minRho= -Y;  

thetas= unique( [(-pi/2)    :thetaSpacing:(pi/2)     (pi/2)] );
thetas= thetas(1:end-1); % remove pi/2 to be in cyclic mode
rhos=   unique( [(minRho):rhoSpacing  :(maxRho) (maxRho)] );          

H= zeros(length(thetas), length(rhos));
expected_average_H_for_uniform_edge_distribution= zeros(length(thetas), length(rhos));

for y=1:Y
    for x=1:X
        
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        % compute expected_average_H_for_uniform_edge_distribution over the current
        % pixel
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        for theta_i= 1:length(thetas)
            
            theta= thetas(theta_i);
            
            rho= x*cos(theta)+y*sin(theta);
            [rho_lb_i, rho_ub_i] = find_lb_ub_in_sorted_arr(rho, rhos);
            
            expected_average_H_for_uniform_edge_distribution(theta_i, rho_lb_i)= expected_average_H_for_uniform_edge_distribution(theta_i, rho_lb_i)+1;
            expected_average_H_for_uniform_edge_distribution(theta_i, rho_ub_i)= expected_average_H_for_uniform_edge_distribution(theta_i, rho_ub_i)+1;
            
        end
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        
        if (gradientImY(y,x)==0&&gradientImX(y,x)==0)
            continue;
        end
        
        theta= atan(gradientImY(y,x)/gradientImX(y,x));
        [theta_lb_i, theta_ub_i] = find_lb_ub_in_sorted_cyclic_arr(theta, thetas, pi/2);
        
        rho= x*cos(theta)+y*sin(theta);
        [rho_lb_i, rho_ub_i] = find_lb_ub_in_sorted_arr(rho, rhos);
        
        grad_magnitude= norm([gradientImY(y,x) gradientImX(y,x)],2);
        
        H(theta_lb_i, rho_lb_i)= H(theta_lb_i, rho_lb_i) + 0.25*grad_magnitude; 
        H(theta_lb_i, rho_ub_i)= H(theta_lb_i, rho_ub_i) + 0.25*grad_magnitude; 
        H(theta_ub_i, rho_lb_i)= H(theta_ub_i, rho_lb_i) + 0.25*grad_magnitude; 
        H(theta_ub_i, rho_ub_i)= H(theta_ub_i, rho_ub_i) + 0.25*grad_magnitude; 
        
    end
end