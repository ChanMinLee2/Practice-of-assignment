import tkinter as tk
from tkinter import messagebox
from tkinter import simpledialog

class TodoApp:
    def __init__(self, master):
        self.master = master
        self.master.title("mine.Todo")
        
        self.current_view = "daily"
        self.daily_tasks = []
        self.weekly_tasks = []
        self.monthly_tasks = []

        self.create_widgets()

    def create_widgets(self):
        self.lbl_title = tk.Label(self.master, text="mine.Todo", font=("Arial", 18))
        self.lbl_title.grid(row=0, column=0, columnspan=3)

        self.lbl_current_view = tk.Label(self.master, text="Daily", font=("Arial", 12))
        self.lbl_current_view.grid(row=1, column=0, columnspan=3)

        self.listbox_tasks = tk.Listbox(self.master, width=50)
        self.listbox_tasks.grid(row=2, column=0, columnspan=3)

        self.btn_add_task = tk.Button(self.master, text="Add Task", command=self.add_task)
        self.btn_add_task.grid(row=3, column=0)

        self.btn_remove_task = tk.Button(self.master, text="Remove Task", command=self.remove_task)
        self.btn_remove_task.grid(row=3, column=1)

        self.btn_change_view = tk.Button(self.master, text="Change View", command=self.change_view)
        self.btn_change_view.grid(row=3, column=2)

        self.refresh_tasks()

    def add_task(self):
        task = simpledialog.askstring("Add Task", "Enter task:")
        if task:
            if self.current_view == "daily":
                self.daily_tasks.append(task)
            elif self.current_view == "weekly":
                self.weekly_tasks.append(task)
            else:
                self.monthly_tasks.append(task)
            self.refresh_tasks()

    def remove_task(self):
        selected_index = self.listbox_tasks.curselection()
        if selected_index:
            if self.current_view == "daily":
                del self.daily_tasks[selected_index[0]]
            elif self.current_view == "weekly":
                del self.weekly_tasks[selected_index[0]]
            else:
                del self.monthly_tasks[selected_index[0]]
            self.refresh_tasks()

    def change_view(self):
        if self.current_view == "daily":
            self.current_view = "weekly"
            self.lbl_current_view.config(text="Weekly")
        elif self.current_view == "weekly":
            self.current_view = "monthly"
            self.lbl_current_view.config(text="Monthly")
        else:
            self.current_view = "daily"
            self.lbl_current_view.config(text="Daily")
        self.refresh_tasks()

    def refresh_tasks(self):
        self.listbox_tasks.delete(0, tk.END)
        if self.current_view == "daily":
            for task in self.daily_tasks:
                self.listbox_tasks.insert(tk.END, task)
        elif self.current_view == "weekly":
            for task in self.weekly_tasks:
                self.listbox_tasks.insert(tk.END, task)
        else:
            for task in self.monthly_tasks:
                self.listbox_tasks.insert(tk.END, task)

def main():
    root = tk.Tk()
    app = TodoApp(root)
    root.mainloop()

if __name__ == "__main__":
    main()
