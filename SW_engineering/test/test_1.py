import random

# 영어 단어 데이터베이스
word_database = {
    'apple': '사과',
    'banana': '바나나',
    'cherry': '체리',
    'dog': '개',
    'cat': '고양이',
    # 추가적인 단어는 필요에 따라 여기에 추가
}

# 사용자 정보 데이터베이스
user_database = {
    'user': 'password',
    'admin': 'admin_password',
    # 추가적인 사용자 정보는 필요에 따라 여기에 추가
}

# 로그인 함수
def login():
    username = input("사용자 이름을 입력하세요: ")
    password = input("비밀번호를 입력하세요: ")
    if username in user_database and user_database[username] == password:
        return username
    else:
        print("잘못된 사용자 이름 또는 비밀번호입니다.")
        return None

# 학습 함수
def study():
    words = list(word_database.keys())
    random.shuffle(words)
    for word in words:
        print("영어 단어:", word)
        input("뜻을 확인하려면 엔터를 누르세요.")
        print("뜻:", word_database[word])

# 테스트 함수
def test():
    score = 0
    words = list(word_database.keys())
    random.shuffle(words)
    for word in words[:5]:
        print("뜻:", word_database[word])
        answer = input("위 단어의 영어 단어를 입력하세요: ")
        if answer.lower() == word.lower():
            print("정답입니다!")
            score += 1
        else:
            print("틀렸습니다. 정답은", word, "입니다.")
    print("테스트 결과: {}개 중 {}개 정답".format(5, score))

# 관리자 함수
def admin(username):
    if username == 'admin':
        print("관리자 모드입니다.")
        action = input("원하는 작업을 선택하세요 (C: 추가, R: 조회, U: 수정, D: 삭제): ").upper()
        if action == 'C':
            eng_word = input("추가할 영어 단어를 입력하세요: ")
            kor_meaning = input("추가할 단어의 뜻을 입력하세요: ")
            word_database[eng_word] = kor_meaning
            print("단어가 추가되었습니다.")
        elif action == 'R':
            for eng_word, kor_meaning in word_database.items():
                print("{}: {}".format(eng_word, kor_meaning))
        elif action == 'U':
            eng_word = input("수정할 영어 단어를 입력하세요: ")
            if eng_word in word_database:
                kor_meaning = input("새로운 뜻을 입력하세요: ")
                word_database[eng_word] = kor_meaning
                print("단어가 수정되었습니다.")
            else:
                print("해당 단어가 데이터베이스에 없습니다.")
        elif action == 'D':
            eng_word = input("삭제할 영어 단어를 입력하세요: ")
            if eng_word in word_database:
                del word_database[eng_word]
                print("단어가 삭제되었습니다.")
            else:
                print("해당 단어가 데이터베이스에 없습니다.")
        else:
            print("잘못된 선택입니다.")
    else:
        print("관리자 권한이 없습니다.")

# 메인 함수
def main():
    while True:
        print("\n1. 로그인")
        print("2. 종료")
        choice = input("원하는 작업을 선택하세요: ")

        if choice == '1':
            username = login()
            if username:
                while True:
                    print("\n1. 학습")
                    print("2. 단어 테스트")
                    if username == 'admin':
                        print("3. 관리자 모드")
                    print("4. 로그아웃")
                    option = input("원하는 작업을 선택하세요: ")

                    if option == '1':
                        study()
                    elif option == '2':
                        test()
                    elif option == '3' and username == 'admin':
                        admin(username)
                    elif option == '4':
                        print("로그아웃합니다.")
                        break
                    else:
                        print("잘못된 선택입니다.")
        elif choice == '2':
            print("프로그램을 종료합니다.")
            break
        else:
            print("잘못된 선택입니다.")

if __name__ == "__main__":
    main()
