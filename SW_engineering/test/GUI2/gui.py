import tkinter as tk
from tkinter import font as tkfont

class LoginApp(tk.Tk):
    def __init__(self):
        super().__init__()
        
        self.title("로그인")
        self.geometry("400x300")
        self.configure(bg="white")

        # Configure fonts
        self.title_font = tkfont.Font(family="Helvetica", size=24, weight="bold")
        self.entry_font = tkfont.Font(family="Helvetica", size=12)
        self.button_font = tkfont.Font(family="Helvetica", size=12)

        # Title label
        self.title_label = tk.Label(self, text="로그인", font=self.title_font, bg="white")
        self.title_label.pack(pady=(30, 20))

        # Username entry
        self.username_entry = tk.Entry(self, font=self.entry_font, width=30, bd=2, relief="solid")
        self.username_entry.insert(0, "사용자 명")
        self.username_entry.pack(pady=(0, 10))

        # Password entry
        self.password_entry = tk.Entry(self, font=self.entry_font, width=30, bd=2, relief="solid", show="*")
        self.password_entry.insert(0, "비밀번호")
        self.password_entry.pack(pady=(0, 20))

        # Frame for button and link
        self.bottom_frame = tk.Frame(self, bg="white")
        self.bottom_frame.pack(pady=(0, 20))

        # Create account link
        self.create_account_label = tk.Label(self.bottom_frame, text="계정 만들기", font=self.entry_font, fg="#4285F4", bg="white", cursor="hand2")
        self.create_account_label.pack(side="left", padx=(0, 20))

        # Login button
        self.login_button = tk.Button(self.bottom_frame, text="로그인", font=self.button_font, bg="#4285F4", fg="white", command=self.login)
        self.login_button.pack(side="left")

    def login(self):
        # Placeholder for the login function
        username = self.username_entry.get()
        password = self.password_entry.get()
        print(f"Username: {username}, Password: {password}")

if __name__ == "__main__":
    app = LoginApp()
    app.mainloop()
