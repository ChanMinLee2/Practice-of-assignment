import tkinter as tk
from tkinter import messagebox, simpledialog
import sqlite3
import random

# SQLite 데이터베이스 초기화 함수
def initialize_database():
    conn = sqlite3.connect('word_database.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS words (
                        english TEXT PRIMARY KEY,
                        korean TEXT,
                        difficulty TEXT)''')
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        username TEXT PRIMARY KEY,
                        password TEXT)''')
    # 기본 사용자 추가
    cursor.execute('''INSERT OR IGNORE INTO users (username, password) VALUES
                        ('user', 'password'),
                        ('admin', 'admin_password')''')
    conn.commit()
    conn.close()

# 회원가입 함수
def register():
    # 새로운 창 생성
    register_window = tk.Toplevel()
    register_window.title("회원가입")

    # 사용자 이름 입력란 추가
    username_label = tk.Label(register_window, text="사용자 이름:")
    username_label.grid(row=0, column=0, pady=5, padx=10)
    username_entry = tk.Entry(register_window)
    username_entry.grid(row=0, column=1, pady=5, padx=10)

    # 비밀번호 입력란 추가
    password_label = tk.Label(register_window, text="비밀번호:")
    password_label.grid(row=1, column=0, pady=5, padx=10)
    password_entry = tk.Entry(register_window, show='*')
    password_entry.grid(row=1, column=1, pady=5, padx=10)

    def validate_register():
        username = username_entry.get()
        password = password_entry.get()

        if username and password:
            conn = sqlite3.connect('word_database.db')
            cursor = conn.cursor()

            cursor.execute('SELECT * FROM users WHERE username = ?', (username,))
            existing_user = cursor.fetchone()

            if existing_user:
                messagebox.showerror("회원가입 오류", "중복된 아이디입니다. 다시 입력해주세요.")
            else:
                cursor.execute('INSERT INTO users (username, password) VALUES (?, ?)', (username, password))
                conn.commit()
                conn.close()
                messagebox.showinfo("알림", "회원가입이 완료되었습니다. 이제 로그인해주세요.")
                register_window.destroy()  # 창 닫기

    # 확인 버튼 추가
    register_button = tk.Button(register_window, text="확인", command=validate_register)
    register_button.grid(row=2, column=0, columnspan=2, pady=10)

# 로그인 함수
def login():
    global current_user
    username = simpledialog.askstring("Login", "사용자 이름을 입력하세요:")
    password = simpledialog.askstring("Login", "비밀번호를 입력하세요:", show='*')
    
    conn = sqlite3.connect('word_database.db')
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM users WHERE username = ? AND password = ?', (username, password))
    user = cursor.fetchone()
    conn.close()
    
    if user:
        current_user = username
        update_status(f"로그인: {username}")
        show_main_menu()
    else:
        messagebox.showerror("로그인 오류", "잘못된 사용자 이름 또는 비밀번호입니다.")

def show_login_menu():
    for widget in main_frame.winfo_children():
        widget.pack_forget()
    register_button.pack(pady=10)
    login_button.pack(pady=10)
    exit_button.pack(pady=10)

def show_main_menu():
    for widget in main_frame.winfo_children():
        widget.pack_forget()
    study_button.pack(pady=10)
    test_button.pack(pady=10)
    if current_user == 'admin':
        admin_button.pack(pady=10)
    logout_button.pack(pady=10)

def login():
    global current_user
    username = simpledialog.askstring("로그인", "사용자 이름을 입력하세요:")
    password = simpledialog.askstring("로그인", "비밀번호를 입력하세요:", show='*')
    
    conn = sqlite3.connect('word_database.db')
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM users WHERE username = ? AND password = ?', (username, password))
    user = cursor.fetchone()
    conn.close()
    
    if user:
        current_user = username
        update_status(f"로그인: {username}")
        show_main_menu()
    else:
        messagebox.showerror("로그인 오류", "잘못된 사용자 이름 또는 비밀번호입니다.")

def register_and_show_login_menu():
    register()
    show_login_menu()

# 학습 함수
def study():
    conn = sqlite3.connect('word_database.db')
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM words')
    words = cursor.fetchall()
    random.shuffle(words)
    for word, meaning, difficulty in words:
        messagebox.showinfo("영어 단어", f"영어 단어: {word}\n뜻: {meaning}\n난이도: {difficulty}")
    conn.close()

# 테스트 함수
def test():
    score = 0
    conn = sqlite3.connect('word_database.db')
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM words')
    words = cursor.fetchall()
    random.shuffle(words)
    for word, meaning, difficulty in words[:5]:
        answer = simpledialog.askstring("단어 테스트", f"뜻: {meaning}\n난이도: {difficulty}\n위 단어의 영어 단어를 입력하세요:")
        if answer and answer.lower() == word.lower():
            messagebox.showinfo("정답!", "정답입니다!")
            score += 1
        else:
            messagebox.showinfo("오답", f"틀렸습니다. 정답은 {word} 입니다.")
    messagebox.showinfo("테스트 결과", f"테스트 결과: 5개 중 {score}개 정답")
    conn.close()

# 단어 목록 갱신 함수
def refresh_word_list():
    for widget in word_list_frame.winfo_children():
        widget.destroy()
    
    conn = sqlite3.connect('word_database.db')
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM words ORDER BY english')
    words = cursor.fetchall()
    conn.close()
    
    for word, meaning, difficulty in words:
        word_frame = tk.Frame(word_list_frame, bg="#f0f0f0", padx=5, pady=5, relief=tk.RAISED, bd=2)
        word_frame.pack(fill="x", pady=2)
        
        word_label = tk.Label(word_frame, text=f"{word}: {meaning} (난이도: {difficulty})", anchor="w", bg="#f0f0f0")
        word_label.pack(side="left", fill="x", expand=True)
        
        delete_button = tk.Button(word_frame, text="삭제하기", command=lambda w=word: delete_word(w), bg="#f44336", fg="white", padx=5, pady=2)
        delete_button.pack(side="right")
        
        edit_button = tk.Button(word_frame, text="수정하기", command=lambda w=word: edit_word(w), bg="#4caf50", fg="white", padx=5, pady=2)
        edit_button.pack(side="right", padx=5)

# 단어 수정 함수
def edit_word(word):
    new_meaning = simpledialog.askstring("단어 수정", f"{word}의 새로운 뜻을 입력하세요:")
    new_difficulty = simpledialog.askstring("단어 수정", f"{word}의 새로운 난이도를 입력하세요:")
    if new_meaning and new_difficulty:
        conn = sqlite3.connect('word_database.db')
        cursor = conn.cursor()
        cursor.execute('UPDATE words SET korean = ?, difficulty = ? WHERE english = ?', (new_meaning, new_difficulty, word))
        conn.commit()
        conn.close()
        messagebox.showinfo("알림", "단어가 수정되었습니다.")
        refresh_word_list()

# 단어 삭제 함수
def delete_word(word):
    conn = sqlite3.connect('word_database.db')
    cursor = conn.cursor()
    cursor.execute('DELETE FROM words WHERE english = ?', (word,))
    conn.commit()
    conn.close()
    messagebox.showinfo("알림", "단어가 삭제되었습니다.")
    refresh_word_list()

# 단어 추가 함수
def add_word():
    eng_word = simpledialog.askstring("추가", "추가할 영어 단어를 입력하세요:")
    kor_meaning = simpledialog.askstring("추가", "추가할 단어의 뜻을 입력하세요:")
    difficulty = simpledialog.askstring("추가", "추가할 단어의 난이도를 입력하세요:")
    if eng_word and kor_meaning and difficulty:
        conn = sqlite3.connect('word_database.db')
        cursor = conn.cursor()
        cursor.execute('INSERT OR IGNORE INTO words (english, korean, difficulty) VALUES (?, ?, ?)', (eng_word, kor_meaning, difficulty))
        conn.commit()
        conn.close()
        messagebox.showinfo("알림", "단어가 추가되었습니다.")
        refresh_word_list()

# 관리자 모드 함수
def admin():
    if current_user == 'admin':
        show_admin_menu()
    else:
        messagebox.showerror("권한 오류", "관리자 권한이 없습니다.")

def logout():
    global current_user
    current_user = None
    update_status("로그아웃 되었습니다.")
    show_login_menu()

def update_status(message):
    status_label.config(text=message)

def show_admin_menu():
    for widget in main_frame.winfo_children():
        widget.pack_forget()
    word_list_frame.pack(fill="both", expand=True)
    add_word_button.pack(pady=10)
    back_button.pack(pady=10)
    refresh_word_list()

# 메인 함수
def main():
    initialize_database()
    show_login_menu()

if __name__ == "__main__":
    # Tkinter 초기화
    root = tk.Tk()
    root.title("단어 학습 프로그램")
    root.geometry("500x400")
    root.configure(bg="#e0f7fa")

    current_user = None

    # 메인 프레임
    main_frame = tk.Frame(root, bg="#e0f7fa")
    main_frame.pack(pady=20)

    # 상태 표시 라벨
    status_label = tk.Label(root, text="로그인 필요", bd=1, relief=tk.SUNKEN, anchor=tk.W, bg="#006064", fg="white")
    status_label.pack(side=tk.BOTTOM, fill=tk.X)

    # 로그인 및 회원가입 버튼
    register_button = tk.Button(main_frame, text="회원가입", command=register_and_show_login_menu, width=15, bg="#64b5f6", fg="white", pady=5)
    login_button = tk.Button(main_frame, text="로그인", command=login, width=15, bg="#00796b", fg="white", pady=5)
    exit_button = tk.Button(main_frame, text="종료", command=root.quit, width=15, bg="#d32f2f", fg="white", pady=5)

    # 메인 메뉴
    study_button = tk.Button(main_frame, text="학습", command=study, width=20, bg="#0288d1", fg="white", pady=5)
    test_button = tk.Button(main_frame, text="단어 테스트", command=test, width=20, bg="#0288d1", fg="white", pady=5)
    admin_button = tk.Button(main_frame, text="관리자 모드", command=admin, width=20, bg="#c2185b", fg="white", pady=5)
    logout_button = tk.Button(main_frame, text="로그아웃", command=logout, width=20, bg="#455a64", fg="white", pady=5)

    # 관리자 메뉴
    word_list_frame = tk.Frame(main_frame, bg="#e0f7fa")
    add_word_button = tk.Button(main_frame, text="단어 추가", command=add_word, width=15, bg="#4caf50", fg="white", pady=5)
    back_button = tk.Button(main_frame, text="뒤로가기", command=show_main_menu, width=15, bg="#757575", fg="white", pady=5)

    main()
    root.mainloop()