import pyautogui
import time
from pynput import keyboard

# 全局变量，用于控制auto()函数的运行
running = True

# 监听键盘事件
def on_press(key):
    global running
    if key == keyboard.Key.esc:
        # 如果按下ESC键，则停止auto()函数的执行
        running = False

# 创建并启动键盘监听器
keyboard_listener = keyboard.Listener(on_press=on_press)
keyboard_listener.start()

def auto():
    # 移动鼠标到固定位置 (x, y)
    x, y = 210, 200  # 你可以根据需要修改坐标
    pyautogui.moveTo(x, y, duration=1)  # 移动鼠标到指定位置，duration为移动持续时间（秒）

    # 等待一小会儿，确保鼠标已到达指定位置
    time.sleep(0.5)

    # 执行双击操作
    pyautogui.doubleClick()  # 双击鼠标左键
    time.sleep(0.5)

    # 把鼠标移动到 1885，300，然后双击
    pyautogui.moveTo(1885, 300, duration=1)
    pyautogui.doubleClick()
    time.sleep(0.5)

    # 键盘执行Ctrl+F
    pyautogui.hotkey('ctrl', 'f')
    time.sleep(0.5)

    # 键盘输入introduce
    pyautogui.typewrite('Models')
    time.sleep(0.5)

    # 键盘执行 回车键
    pyautogui.press('enter')
    time.sleep(0.5)

    # 鼠标移动到1394，305
    pyautogui.moveTo(1394, 305)
    time.sleep(0.5)

    # 鼠标单击
    pyautogui.click()
    time.sleep(0.5)

    # 键盘输入AAAAAA
    pyautogui.typewrite('AAAAAA')
    time.sleep(0.5)

    # 键盘执行 回车键
    pyautogui.press('enter')
    time.sleep(0.5)

    # 键盘执行 Ctrl + S
    pyautogui.hotkey('ctrl', 's')
    time.sleep(0.5)

    # 键盘执行 Alt + F4
    pyautogui.hotkey('alt', 'f4')
    time.sleep(0.5)

    # 鼠标移动到210, 200
    pyautogui.moveTo(1000,800)
    time.sleep(0.5)

    # 鼠标单击
    pyautogui.click()
    time.sleep(0.5)

    # 鼠标移动到210, 200
    pyautogui.moveTo(533,142)
    time.sleep(0.5)


    # 鼠标单击
    pyautogui.click()
    time.sleep(0.5)

    # 鼠标单击
    pyautogui.click()
    time.sleep(0.5)


if __name__ == "__main__":
    # 创建并启动键盘监听器
    with keyboard.Listener(on_press=on_press) as keyboard_listener:
        try:
            while running:
                auto()  # 调用auto()函数
                if not running:
                    break  # 如果running为False，则退出循环
        except KeyboardInterrupt:
            # 如果用户通过键盘中断（例如Ctrl+C）来停止程序
            running = False
        finally:
            print("程序已退出。")