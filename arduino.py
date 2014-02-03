import serial
import pyHook
import pythoncom
import ctypes

__ser = serial.Serial('COM17', 9600, timeout=0)

def OnMouseDown(event):
  __ser.write("1")
  return True

def OnMouseUp(event):
  __ser.write("0")
  return True

def OnEscapePress(event):
  if event.Key == "Escape":
    ctypes.windll.user32.PostQuitMessage(0) #sends WM_QUIT signal to stop pythoncom.pumpmessages
  return True

def main():
  hm = pyHook.HookManager()
  hm.SubscribeMouseAllButtonsDown(OnMouseDown)
  hm.SubscribeMouseAllButtonsUp(OnMouseUp)
  hm.SubscribeKeyDown(OnEscapePress)
  hm.HookMouse()
  hm.HookKeyboard()
  pythoncom.PumpMessages() #pythoncom module is used to capture the key messages.
  hm.UnhookMouse()  
  hm.UnhookKeyboard()
    

if __name__ == "__main__":
  main()
