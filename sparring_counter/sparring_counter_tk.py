import tkinter as tk

class SparringCounter: 
    def __init__(self):
        self.start_win = tk.Tk()
        self.start_win.title('Sparring Counter')
        self.start_win.geometry('500x300+0+0') 
        self.start_win.grid_columnconfigure(3, weight=1)    
        self.start_button = tk.Button(self.start_win, text='Start', command=self.startCount, pady=5)
        self.start_button.grid(row=0, columnspan=4, sticky='ew')
        tk.Label(self.start_win, text='Red Name: ').grid(row=1, column=0)
        self.red_name = tk.Entry(self.start_win, width=10)
        self.red_name.grid(row=1,column=1)
        tk.Label(self.start_win, text='Blue Name: ').grid(row=1, column=2)
        self.blue_name = tk.Entry(self.start_win, width=10)
        self.blue_name.grid(row=1,column=3)
        tk.mainloop()
        
    def startCount(self):
        self.count_win = tk.Tk()
        self.count_win.geometry('500x300')
        self.count_win.bind('<KeyPress>', self.keyPressed)
        self.red_count = 0
        self.blue_count = 0
        self.red = tk.Frame(self.count_win)
        self.blue = tk.Frame(self.count_win)
        self.red.pack(side='left')
        self.blue.pack(side='right')
        tk.Label(self.red, text=self.red_name.get(), pady=5, font=('Helvetica', 30)).pack()
        tk.Label(self.blue, text=self.blue_name.get(), pady=5, font=('Helvetica', 30)).pack()
        self.red_count_label = tk.Label(self.red, text=self.red_count, pady=5, bg='red', fg='white', font=('Helvetica', 30))
        self.red_count_label.pack()
        self.blue_count_label = tk.Label(self.blue, text=self.blue_count, pady=5, bg='blue', fg='white', font=('Helvetica', 30))
        self.blue_count_label.pack()
        # self.red_name.grid()
        
    def keyPressed(self, event):
        c = event.char
        if c == 'q':
            self.red_count += 1
        elif c == 'a':
            self.blue_count += 1
        elif c == 'e' and self.red_count > 0:
            self.red_count -= 1
        elif c == 'd' and self.blue_count > 0:
            self.blue_count -= 1
        self.red_count_label.config(text=self.red_count)
        self.blue_count_label.config(text=self.blue_count)
        
if __name__ == '__main__':
    sparring_counter = SparringCounter()
        
    