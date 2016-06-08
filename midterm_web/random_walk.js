random_walk(1);

function random_walk(n){
    n++;
    if (n%4 ==0) {
        moveLeft(5);
        setTimeout("moveLeft(4)",10);
        setTimeout("moveLeft(3)",40);
        setTimeout("moveLeft(2)",90);
        setTimeout("moveLeft(1)",160);
    }
    else if (n%4==1) {
        moveRight(5);
        setTimeout("moveRight(4)",10);
        setTimeout("moveRight(3)",40);
        setTimeout("moveRight(2)",90);
        setTimeout("moveRight(1)",160);
    }
    else if (n%4==2) {
        moveDown(5);
        setTimeout("moveDown(4)",10);
        setTimeout("moveDown(3)",40);
        setTimeout("moveDown(2)",90);
        setTimeout("moveDown(1)",160);
    }
    else {
        moveUp(5);
        setTimeout("moveUp(4)",10);
        setTimeout("moveUp(3)",40);
        setTimeout("moveUp(2)",90);
        setTimeout("moveUp(1)",160);
    }
    
    setTimeout("random_walk(usefloor(0,10))",150);
}

function usefloor(min,max) {
    return Math.floor(Math.random()*(max-min+1)+min);
}

function control(){
    
    ek=event.keyCode;
    if (ek==37) {
        moveLeft(5);
        setTimeout("moveLeft(4)",10);
        setTimeout("moveLeft(3)",40);
        setTimeout("moveLeft(2)",90);
        setTimeout("moveLeft(1)",160);
    }
    if (ek==39) {
        moveRight(5);
        setTimeout("moveRight(4)",10);
        setTimeout("moveRight(3)",40);
        setTimeout("moveRight(2)",90);
        setTimeout("moveRight(1)",160);
    }
    if (ek==38) {
        moveDown(5);
        setTimeout("moveDown(4)",10);
        setTimeout("moveDown(3)",40);
        setTimeout("moveDown(2)",90);
        setTimeout("moveDown(1)",160);
    }
    if (ek==40) {
        moveUp(5);
        setTimeout("moveUp(4)",10);
        setTimeout("moveUp(3)",40);
        setTimeout("moveUp(2)",90);
        setTimeout("moveUp(1)",160);
    }
}
document.onkeydown=control;

function moveLeft(x){
    imageDiv.style.posLeft-=x;
    if (imageDiv.style.posLeft < 0){
        imageDiv.style.posLeft =0;
    }
}
function moveRight(x){
    imageDiv.style.posLeft+=x;
    if (imageDiv.style.posLeft > 500){
        imageDiv.style.posLeft =500;
    }
}
function moveDown(x){
    imageDiv.style.posTop-=x;
    if (imageDiv.style.posTop < -300){
        imageDiv.style.posTop =-300;
    }
}
function moveUp(x){
    imageDiv.style.posTop+=x;
    if (imageDiv.style.posTop > -90){
        imageDiv.style.posTop =-90;
    }
}