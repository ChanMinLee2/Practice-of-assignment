import tkinter as tk
from tkinter import messagebox, simpledialog
import sqlite3
import random

# SQLite 데이터베이스 초기화 함수
def initialize_database():
    conn = sqlite3.connect('word_database.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS word_data (
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

# 로그인 함수
def login():
    global current_user
    username = simpledialog.askstring("Login", "사용자 이름을 입력하세요:")
    password = simpledialog.askstring("Login", "비밀번호를 입력하세요:", show='*')
    
    conn = sqlite3.connect('word_database.db')
    cursor = conn.cursor()
    user = cursor.execute('SELECT * FROM users WHERE username = ? AND password = ?', (username, password)).fetchone()
    conn.close()
    
    if user:
        current_user = username
        update_status(f"로그인: {username}")
        show_main_menu()
    else:
        messagebox.showerror("로그인 오류", "잘못된 사용자 이름 또는 비밀번호입니다.")

# 단어 테스트 함수
def test(level, num_questions):
    global answer_entries, questions
    answer_entries = []
    questions = []

    conn = sqlite3.connect('word_database.db')
    cursor = conn.cursor()
    cursor.execute('SELECT english, korean, difficulty FROM word_data WHERE difficulty = ? ORDER BY RANDOM() LIMIT ?', (level, num_questions))
    words = cursor.fetchall()
    conn.close()
    
    for widget in main_frame.winfo_children():
        widget.pack_forget()
    
    question_frame = tk.Frame(main_frame, bg="#e0f7fa")
    question_frame.pack(pady=20)

    for i, (english, korean, difficulty) in enumerate(words):
        question_label = tk.Label(question_frame, text=f"{i+1}. ({difficulty}) {korean}", anchor="w", bg="#e0f7fa")
        question_label.pack(fill="x")
        
        answer_entry = tk.Entry(question_frame)
        answer_entry.pack(fill="x", pady=5)
        
        answer_entries.append(answer_entry)
        questions.append((english, korean, difficulty))
    
    submit_button = tk.Button(main_frame, text="테스트 완료", command=show_results, width=20, bg="#0288d1", fg="white", pady=5)
    submit_button.pack(pady=10)

    cancel_button = tk.Button(main_frame, text="취소하기", command=show_main_menu, width=20, bg="#d32f2f", fg="white", pady=5)
    cancel_button.pack(pady=10)

# 사용자 수준 점검 함수
def level_check():
    global answer_entries, questions
    answer_entries = []
    questions = []

    conn = sqlite3.connect('word_database.db')
    cursor = conn.cursor()
    cursor.execute('SELECT english, korean, difficulty FROM word_data ORDER BY RANDOM() LIMIT 20')
    words = cursor.fetchall()
    conn.close()
    
    for widget in main_frame.winfo_children():
        widget.pack_forget()
    
    question_frame = tk.Frame(main_frame, bg="#e0f7fa")
    question_frame.pack(pady=20)

    for i, (english, korean, difficulty) in enumerate(words):
        question_label = tk.Label(question_frame, text=f"{i+1}. ({difficulty}) {korean}", anchor="w", bg="#e0f7fa")
        question_label.pack(fill="x")
        
        answer_entry = tk.Entry(question_frame)
        answer_entry.pack(fill="x", pady=5)
        
        answer_entries.append(answer_entry)
        questions.append((english, korean, difficulty))
    
    submit_button = tk.Button(main_frame, text="테스트 완료", command=show_results, width=20, bg="#0288d1", fg="white", pady=5)
    submit_button.pack(pady=10)

    cancel_button = tk.Button(main_frame, text="취소하기", command=show_main_menu, width=20, bg="#d32f2f", fg="white", pady=5)
    cancel_button.pack(pady=10)

# 결과 페이지 함수
def show_results():
    score = 0
    levels = {1: 0, 2: 0, 3: 0, 4: 0}
    
    for i, entry in enumerate(answer_entries):
        answer = entry.get().strip().lower()
        correct_answer = questions[i][0].lower()
        if answer == correct_answer:
            score += 1
            level = (i // 5) + 1
            levels[level] += 1
    
    for widget in main_frame.winfo_children():
        widget.pack_forget()
    
    result_frame = tk.Frame(main_frame, bg="#e0f7fa")
    result_frame.pack(pady=20)

    result_label = tk.Label(result_frame, text=f"테스트 결과: 20개 중 {score}개 정답", bg="#e0f7fa", font=("Helvetica", 14))
    result_label.pack(pady=10)

    for level, correct_count in levels.items():
        level_label = tk.Label(result_frame, text=f"레벨 {level}: {correct_count}개 정답", bg="#e0f7fa")
        level_label.pack(pady=5)
    
    # 사용자 레벨 출력 추가
    if score <= 5:
        user_level = 1
    elif score <= 10:
        user_level = 2
    elif score <= 15:
        user_level = 3
    else:
        user_level = 4
    
    user_level_label = tk.Label(result_frame, text=f"현재 사용자 레벨: {user_level}", bg="#e0f7fa", font=("Helvetica", 14))
    user_level_label.pack(pady=10)
    
    exit_button = tk.Button(result_frame, text="나가기", command=show_main_menu, width=20, bg="#455a64", fg="white", pady=5)
    exit_button.pack(pady=10)

# 단어 목록 갱신 함수
def refresh_word_list():
    for widget in word_list_frame.winfo_children():
        widget.destroy()
    
    conn = sqlite3.connect('word_database.db')
    cursor = conn.cursor()
    words = cursor.execute('SELECT english, korean, difficulty FROM word_data ORDER BY english').fetchall()
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
        cursor.execute('UPDATE word_data SET korean = ?, difficulty = ? WHERE english = ?', (new_meaning, new_difficulty, word))
        conn.commit()
        conn.close()
        messagebox.showinfo("알림", "단어가 수정되었습니다.")
        refresh_word_list()

# 단어 삭제 함수
def delete_word(word):
    conn = sqlite3.connect('word_database.db')
    cursor = conn.cursor()
    cursor.execute('DELETE FROM word_data WHERE english = ?', (word,))
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
        cursor.execute('INSERT OR IGNORE INTO word_data (english, korean, difficulty) VALUES (?, ?, ?)', (eng_word, kor_meaning, difficulty))
        conn.commit()
        conn.close()
        messagebox.showinfo("알림", "단어가 추가되었습니다.")
        refresh_word_list()
    else:
        messagebox.showerror("오류", "영어 단어, 뜻, 난이도를 모두 입력해야 합니다.")

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

def show_login_menu():
    for widget in main_frame.winfo_children():
        widget.pack_forget()
    login_button.pack(pady=10)
    exit_button.pack(pady=10)

def show_main_menu():
    for widget in main_frame.winfo_children():
        widget.pack_forget()
    start_test_button.pack(pady=10)  # 일반 단어 맞추기 버튼
    level_check_button.pack(pady=10)  # 내 수준 점검하기 버튼
    if current_user == 'admin':
        admin_button.pack(pady=10)  # 단어 관리 버튼
    logout_button.pack(pady=10)  # 로그아웃 버튼

def show_admin_menu():
    for widget in main_frame.winfo_children():
        widget.pack_forget()
    word_list_frame.pack(fill="both", expand=True)
    add_word_button.pack(pady=10)
    back_button.pack(pady=10)
    refresh_word_list()

# 새로운 단어 테스트 시작 함수
def start_test():
    level = simpledialog.askstring("단어 테스트", "원하는 문제 레벨을 입력하세요 (예: easy, medium, hard):")
    num_questions = simpledialog.askinteger("단어 테스트", "문제 개수를 입력하세요 (최대 20개):")
    if level and num_questions:
        test(level, num_questions)

# 메인 함수
def main():
    initialize_database()
    show_login_menu()

if __name__ == "__main__":
    # Tkinter 초기화
    root = tk.Tk()
    root.title("단어 학습 프로그램")
    root.geometry("500x600")
    root.configure(bg="#e0f7fa")

    current_user = None
    answer_entries = []
    questions = []

    # 메인 프레임
    main_frame = tk.Frame(root, bg="#e0f7fa")
    main_frame.pack(pady=20, fill="both", expand=True)

    # 상태 표시 라벨
    status_label = tk.Label(root, text="로그인 필요", bd=1, relief=tk.SUNKEN, anchor=tk.W, bg="#006064", fg="white")
    status_label.pack(side=tk.BOTTOM, fill=tk.X)

    # 로그인 메뉴
    login_button = tk.Button(main_frame, text="로그인", command=login, width=15, bg="#00796b", fg="white", pady=5)
    exit_button = tk.Button(main_frame, text="종료", command=root.quit, width=15, bg="#d32f2f", fg="white", pady=5)

    # 메인 메뉴
    start_test_button = tk.Button(main_frame, text="단어 테스트", command=start_test, width=20, bg="#0288d1", fg="white", pady=5)  # 추가된 부분 1
    level_check_button = tk.Button(main_frame, text="내 수준 점검하기", command=level_check, width=20, bg="#0288d1", fg="white", pady=5)  # 수정된 부분 1
    admin_button = tk.Button(main_frame, text="단어 관리", command=admin, width=20, bg="#c2185b", fg="white", pady=5)  # 수정된 부분 3
    logout_button = tk.Button(main_frame, text="로그아웃", command=logout, width=20, bg="#455a64", fg="white", pady=5)  # 수정된 부분 4

    # 관리자 메뉴
    word_list_frame = tk.Frame(main_frame, bg="#e0f7fa")
    add_word_button = tk.Button(main_frame, text="단어 추가", command=add_word, width=15, bg="#4caf50", fg="white", pady=5)
    back_button = tk.Button(main_frame, text="뒤로가기", command=show_main_menu, width=15, bg="#757575", fg="white", pady=5)

    main()
    root.mainloop()
