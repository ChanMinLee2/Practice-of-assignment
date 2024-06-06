from PIL import ImageGrab, Image

# 클립보드에서 이미지 가져오기
def get_clipboard_image():
    try:
        # 클립보드에 있는 이미지를 가져옴
        image = ImageGrab.grabclipboard()
        if isinstance(image, Image.Image):
            return image
        else:
            print("클립보드에 이미지가 없습니다.")
            return None
    except Exception as e:
        print(f"이미지를 가져오는 중 오류가 발생했습니다: {e}")
        return None

# 이미지 파일로 저장
def save_image(image, file_path):
    try:
        image.save(file_path)
        print(f"이미지를 {file_path}로 저장했습니다.")
    except Exception as e:
        print(f"이미지를 저장하는 중 오류가 발생했습니다: {e}")

# 메인 실행 부분
if __name__ == "__main__":
    image = get_clipboard_image()
    if image:
        save_image(image, "saved_image.png")
