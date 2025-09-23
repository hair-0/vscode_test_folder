document.addEventListener('DOMContentLoaded', () => {
    // 获取Canvas元素和上下文
    const canvas = document.getElementById('game-canvas');
    const ctx = canvas.getContext('2d');
    
    // 游戏配置
    const gridSize = 20; // 网格大小
    const tileCount = canvas.width / gridSize; // 网格数量
    let speed = 7; // 游戏速度
    
    // 游戏状态
    let gameRunning = false;
    let gameOver = false;
    let gamePaused = false; // 新增暂停状态
    
    // 蛇的初始位置和速度
    let snake = [];
    let velocityX = 0;
    let velocityY = 0;
    
    // 食物位置
    let foodX;
    let foodY;
    
    // 分数
    let score = 0;
    
    // 获取DOM元素
    const scoreElement = document.getElementById('score');
    const finalScoreElement = document.getElementById('final-score');
    const gameOverElement = document.getElementById('game-over');
    const startButton = document.getElementById('start-btn');
    const restartButton = document.getElementById('restart-btn');
    const pauseButton = document.createElement('button'); // 创建暂停按钮
    pauseButton.id = 'pause-btn';
    pauseButton.textContent = '暂停';
    pauseButton.style.display = 'none';
    document.querySelector('.controls').appendChild(pauseButton); // 添加到控制区域
    
    // 初始化游戏
    function initGame() {
        // 重置蛇
        snake = [
            {x: 10, y: 10}
        ];
        
        // 重置速度
        velocityX = 0;
        velocityY = 0;
        
        // 重置分数
        score = 0;
        scoreElement.textContent = score;
        
        // 生成食物
        placeFood();
        
        // 重置游戏状态
        gameOver = false;
        gameOverElement.style.display = 'none';
    }
    
    // 开始游戏
    function startGame() {
        if (!gameRunning) {
            initGame();
            gameRunning = true;
            gamePaused = false; // 重置暂停状态
            startButton.style.display = 'none';
            restartButton.style.display = 'inline-block';
            pauseButton.style.display = 'inline-block'; // 显示暂停按钮
            pauseButton.textContent = '暂停';
            gameLoop();
        }
    }
    
    // 重新开始游戏
    function restartGame() {
        if (gameRunning || gameOver) {
            initGame();
            gameRunning = true;
            gamePaused = false; // 重置暂停状态
            pauseButton.style.display = 'inline-block'; // 显示暂停按钮
            pauseButton.textContent = '暂停';
            gameLoop();
        }
    }
    
    // 暂停/继续游戏
    function togglePause() {
        if (!gameRunning || gameOver) return;
        
        gamePaused = !gamePaused;
        pauseButton.textContent = gamePaused ? '继续' : '暂停';
        
        if (!gamePaused) {
            // 如果从暂停状态恢复，重新开始游戏循环
            gameLoop();
        }
    }
    
    // 随机生成食物
    function placeFood() {
        // 生成随机位置 (避免生成在蛇身上)
        let validPosition = false;
        
        while (!validPosition) {
            foodX = Math.floor(Math.random() * tileCount);
            foodY = Math.floor(Math.random() * tileCount);
            
            // 检查是否与蛇身重叠
            validPosition = true;
            for (let i = 0; i < snake.length; i++) {
                if (snake[i].x === foodX && snake[i].y === foodY) {
                    validPosition = false;
                    break;
                }
            }
        }
    }
    
    // 游戏主循环
    function gameLoop() {
        if (!gameRunning) return;
        
        // 如果游戏结束，停止循环
        if (gameOver) {
            gameRunning = false;
            gameOverElement.style.display = 'block';
            finalScoreElement.textContent = score;
            pauseButton.style.display = 'none'; // 隐藏暂停按钮
            return;
        }
        
        // 如果游戏暂停，不继续执行
        if (gamePaused) return;
        
        setTimeout(() => {
            clearCanvas();
            moveSnake();
            checkCollision();
            drawFood();
            drawSnake();
            
            // 继续循环
            gameLoop();
        }, 1000 / speed);
    }
    
    // 清空画布
    function clearCanvas() {
        ctx.fillStyle = '#222';
        ctx.fillRect(0, 0, canvas.width, canvas.height);
    }
    
    // 绘制蛇
    function drawSnake() {
        ctx.fillStyle = '#4CAF50';
        
        // 绘制蛇身
        for (let i = 0; i < snake.length; i++) {
            ctx.fillRect(
                snake[i].x * gridSize,
                snake[i].y * gridSize,
                gridSize - 1,
                gridSize - 1
            );
        }
        
        // 绘制蛇头 (不同颜色)
        if (snake.length > 0) {
            ctx.fillStyle = '#2E7D32';
            ctx.fillRect(
                snake[0].x * gridSize,
                snake[0].y * gridSize,
                gridSize - 1,
                gridSize - 1
            );
        }
    }
    
    // 绘制食物
    function drawFood() {
        ctx.fillStyle = '#FF5722';
        ctx.fillRect(
            foodX * gridSize,
            foodY * gridSize,
            gridSize - 1,
            gridSize - 1
        );
    }
    
    // 移动蛇
    function moveSnake() {
        // 如果没有移动方向，不移动
        if (velocityX === 0 && velocityY === 0) return;
        
        // 创建新的蛇头 (在当前头部位置基础上移动)
        const head = {
            x: snake[0].x + velocityX,
            y: snake[0].y + velocityY
        };
        
        // 将新头部添加到蛇身前面
        snake.unshift(head);
        
        // 检查是否吃到食物
        if (head.x === foodX && head.y === foodY) {
            // 增加分数
            score += 10;
            scoreElement.textContent = score;
            
            // 每得100分增加速度
            if (score % 100 === 0) {
                speed += 1;
            }
            
            // 生成新食物
            placeFood();
        } else {
            // 如果没吃到食物，移除尾部 (保持长度不变)
            snake.pop();
        }
    }
    
    // 检查碰撞
    function checkCollision() {
        const head = snake[0];
        
        // 检查是否撞墙
        if (head.x < 0 || head.x >= tileCount || head.y < 0 || head.y >= tileCount) {
            gameOver = true;
            return;
        }
        
        // 检查是否撞到自己 (从第二个身体部分开始检查)
        for (let i = 1; i < snake.length; i++) {
            if (head.x === snake[i].x && head.y === snake[i].y) {
                gameOver = true;
                return;
            }
        }
    }
    
    // 键盘控制
    document.addEventListener('keydown', (event) => {
        // 如果游戏没有运行，不处理按键
        if (!gameRunning && !gamePaused) return;
        
        // 暂停/继续游戏 (空格键)
        if (event.key === ' ' || event.key === 'Escape') {
            togglePause();
            return;
        }
        
        // 如果游戏暂停，不处理移动按键
        if (gamePaused) return;
        
        // 根据按键设置移动方向 (防止180度转向)
        switch (event.key) {
            case 'ArrowUp':
            case 'w':
            case 'W':
                if (velocityY !== 1) { // 防止向下时向上转
                    velocityX = 0;
                    velocityY = -1;
                }
                break;
            case 'ArrowDown':
            case 's':
            case 'S':
                if (velocityY !== -1) { // 防止向上时向下转
                    velocityX = 0;
                    velocityY = 1;
                }
                break;
            case 'ArrowLeft':
            case 'a':
            case 'A':
                if (velocityX !== 1) { // 防止向右时向左转
                    velocityX = -1;
                    velocityY = 0;
                }
                break;
            case 'ArrowRight':
            case 'd':
            case 'D':
                if (velocityX !== -1) { // 防止向左时向右转
                    velocityX = 1;
                    velocityY = 0;
                }
                break;
        }
    });
    
    // 按钮事件监听
    startButton.addEventListener('click', startGame);
    restartButton.addEventListener('click', restartGame);
    pauseButton.addEventListener('click', togglePause);
    
    // 键盘控制 - 添加暂停功能
    document.addEventListener('keydown', (event) => {
        // 如果游戏没有运行，不处理按键
        if (!gameRunning && !gamePaused) return;
        
        // 暂停/继续游戏 (空格键)
        if (event.key === ' ' || event.key === 'Escape') {
            togglePause();
            return;
        }
        
        // 如果游戏暂停，不处理移动按键
        if (gamePaused) return;
        
        // 根据按键设置移动方向 (防止180度转向)
        switch (event.key) {
            case 'ArrowUp':
            case 'w':
            case 'W':
                if (velocityY !== 1) { // 防止向下时向上转
                    velocityX = 0;
                    velocityY = -1;
                }
                break;
            case 'ArrowDown':
            case 's':
            case 'S':
                if (velocityY !== -1) { // 防止向上时向下转
                    velocityX = 0;
                    velocityY = 1;
                }
                break;
            case 'ArrowLeft':
            case 'a':
            case 'A':
                if (velocityX !== 1) { // 防止向右时向左转
                    velocityX = -1;
                    velocityY = 0;
                }
                break;
            case 'ArrowRight':
            case 'd':
            case 'D':
                if (velocityX !== -1) { // 防止向左时向右转
                    velocityX = 1;
                    velocityY = 0;
                }
                break;
        }
    });
    
    // 初始绘制
    clearCanvas();
    
    // 添加触摸控制支持
    let touchStartX = 0;
    let touchStartY = 0;
    
    canvas.addEventListener('touchstart', function(e) {
        touchStartX = e.touches[0].clientX;
        touchStartY = e.touches[0].clientY;
        e.preventDefault();
    }, false);
    
    canvas.addEventListener('touchmove', function(e) {
        if (!gameRunning || gamePaused) return;
        
        e.preventDefault();
        let touchEndX = e.touches[0].clientX;
        let touchEndY = e.touches[0].clientY;
        
        let dx = touchEndX - touchStartX;
        let dy = touchEndY - touchStartY;
        
        // 确定主要的滑动方向
        if (Math.abs(dx) > Math.abs(dy)) {
            // 水平滑动
            if (dx > 0 && velocityX !== -1) { // 向右滑动
                velocityX = 1;
                velocityY = 0;
            } else if (dx < 0 && velocityX !== 1) { // 向左滑动
                velocityX = -1;
                velocityY = 0;
            }
        } else {
            // 垂直滑动
            if (dy > 0 && velocityY !== -1) { // 向下滑动
                velocityX = 0;
                velocityY = 1;
            } else if (dy < 0 && velocityY !== 1) { // 向上滑动
                velocityX = 0;
                velocityY = -1;
            }
        }
        
        // 更新起始点，使滑动更流畅
        touchStartX = touchEndX;
        touchStartY = touchEndY;
    }, false);
});