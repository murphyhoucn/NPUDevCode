from pynput import mouse, keyboard

# 全局变量，用于控制监听器的运行
running = True

# 监听鼠标移动事件
def on_move(x, y):
    if running:
        print(f"鼠标当前坐标: ({x}, {y})")

# 监听键盘事件
def on_press(key):
    global running
    if key == keyboard.Key.esc:
        # 如果按下ESC键，则停止监听并设置running为False
        running = False
        return False  # 返回False来停止监听器

# 创建并启动鼠标监听器
mouse_listener = mouse.Listener(on_move=on_move)
mouse_listener.start()

# 创建并启动键盘监听器
keyboard_listener = keyboard.Listener(on_press=on_press)
keyboard_listener.start()

# 等待监听器停止
try:
    while running:
        # 等待一段时间，以便监听器有机会运行
        pass
except KeyboardInterrupt:
    # 如果用户通过键盘中断（例如Ctrl+C）来停止程序
    running = False

# 确保监听器已经停止
mouse_listener.stop()
keyboard_listener.stop()

# 等待监听器线程结束
mouse_listener.join()
keyboard_listener.join()

print("程序已退出。")
