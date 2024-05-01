import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QLineEdit, QPushButton, QMessageBox
import random

# 영어 단어와 한글 뜻 딕셔너리
word_dict = {
    "apple": "사과",
    "banana": "바나나",
    "cherry": "체리",
    # 나머지 단어들을 추가하세요
}

class WordTestApp(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
        self.next_word()

    def initUI(self):
        self.setWindowTitle('영어 단어 테스트')

        self.word_label = QLabel(self)
        self.word_label.move(50, 50)

        self.answer_entry = QLineEdit(self)
        self.answer_entry.move(50, 100)

        self.submit_button = QPushButton('제출', self)
        self.submit_button.move(50, 150)
        self.submit_button.clicked.connect(self.check_answer)

        self.setGeometry(300, 300, 300, 200)

    def next_word(self):
        self.current_word = random.choice(list(word_dict.keys()))
        self.correct_answer = word_dict[self.current_word]
        self.word_label.setText(self.current_word)

    def check_answer(self):
        user_input = self.answer_entry.text().strip().lower()
        if user_input == self.correct_answer:
            QMessageBox.information(self, '결과', '정답입니다!')
        else:
            QMessageBox.critical(self, '결과', f'틀렸습니다. 정답은 "{self.correct_answer}" 입니다.')
        self.answer_entry.clear()
        self.next_word()

def main():
    app = QApplication(sys.argv)
    ex = WordTestApp()
    ex.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
