#ifndef TST_TESTDIVISIONBYZERO_H
#define TST_TESTDIVISIONBYZERO_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <IKeypad.h>
#include <ILatch.h>
#include <lockcontroller.h>

using namespace testing;

// Определяю mock классы
class MockKeypad : public  IKeypad {
public:
    MOCK_METHOD(bool, isActive, (), (override));

    MOCK_METHOD(void, wait, (), (override));

    MOCK_METHOD(PasswordResponse, requestPassword, (), (override));
};


class MockLatch : public ILatch {
public:
    MOCK_METHOD(bool, isActive, (), (override));

    MOCK_METHOD(DoorStatus, open, (), (override));

    MOCK_METHOD(DoorStatus, close, (), (override));

    MOCK_METHOD(DoorStatus, getDoorStatus, (), (override));
};

// Количество вызовов определённых функций
const int NUMBER_OF_CALLS = 1;

TEST(
        // Название набора тестов
        TestLab9,
        // Название теста
        Test1
        )
{
    // Arrange
    // Создаю экзкмпляр интерфейсного класса IKeypad
    MockKeypad myKeypad;
    // Создаю экзкмпляр интерфейсного класса ILatch
    MockLatch myLatch;
    // Создаю экзкмпляр класса LockController и передаю туда myKeypad и myLatch
    LockController myController(&myKeypad, &myLatch);

    // Prepare mocks
    // Метод wait() класса IKeypad будет вызван один раз
    EXPECT_CALL(myKeypad, wait())
        .Times(NUMBER_OF_CALLS)
        .WillOnce(Return());

    // Act
    // Вызывается метод wait() класса LockController
    myController.wait();
}


TEST(TestLab9, Test2) {
    // Arrange
    MockKeypad myKeypad;
    MockLatch myLatch;
    LockController myController(&myKeypad, &myLatch);

    // Prepare mocks
    // Метод getDoorStatus() класса ILatch будет вызван один раз
    EXPECT_CALL(myLatch, getDoorStatus())
        .Times(NUMBER_OF_CALLS)
        .WillOnce(Return(
                      //Дверь закрыта
                      DoorStatus::CLOSE
                      ));

    // Assert
    // Метод isDoorOpen() класса LockController вернёт false
    ASSERT_FALSE(myController.isDoorOpen());
}


TEST(TestLab9, Test3) {
    // Arrange
    MockKeypad myKeypad;
    MockLatch myLatch;
    LockController myController(&myKeypad, &myLatch);

    // Prepare mocks
    // Метод getDoorStatus() класса ILatch будет вызван один раз
    EXPECT_CALL(myLatch, getDoorStatus())
        .Times(NUMBER_OF_CALLS)
        .WillOnce(Return(
                      //Дверь открыта
                      DoorStatus::OPEN
                      ));

    // Assert
    // Метод isDoorOpen() класса LockController вернёт true
    ASSERT_TRUE(myController.isDoorOpen());
}


TEST(TestLab9, Test4) {
    // Arrange
    MockKeypad myKeypad;
    MockLatch myLatch;
    LockController myController(&myKeypad, &myLatch);

    // Prepare mocks
    // Метод open() класса ILatch будет вызван один раз
    EXPECT_CALL(myLatch, open())
        .Times(NUMBER_OF_CALLS)
        .WillOnce(Return(DoorStatus::OPEN));

    // Act
    // Сохраняю статус метода unlockDoor() класса LockController
    DoorStatus myDoorStatus = myController.unlockDoor();

    // Assert
    // Метод unlockDoor() класса LockController вернёт DoorStatus::OPEN
    ASSERT_EQ(myDoorStatus, DoorStatus::OPEN);
}


TEST(TestLab9, Test5) {
    // Arrange
    MockKeypad myKeypad;
    MockLatch myLatch;
    LockController myController(&myKeypad, &myLatch);

    // Prepare mocks
    // Метод close() класса ILatch будет вызван один раз
    EXPECT_CALL(myLatch, close())
        .Times(NUMBER_OF_CALLS)
        .WillOnce(Return(DoorStatus::CLOSE));

    // Act
    // Сохраняю статус метода unlockDoor() класса LockController
    DoorStatus myDoorStatus = myController.unlockDoor();

    // Assert
    // Метод unlockDoor() класса LockController вернёт DoorStatus::CLOSE
    ASSERT_EQ(DoorStatus::CLOSE, myDoorStatus);
}


TEST(TestLab9, Test6) {
    // Arrange
    // Объекты классов IKeypad и ILatch созданы, валидны
    // и переданы в конструктор LockController
    MockKeypad myKeypad;
    MockLatch myLatch;
    LockController myController(&myKeypad, &myLatch);

    // Prepare mocks
    // Метод isActive() класса IKeypad будет вызван один раз
    EXPECT_CALL(myKeypad, isActive())
        .Times(NUMBER_OF_CALLS)
        .WillOnce(Return(true));

    //  Метод isActive() класса ILatch будет вызван один раз
    EXPECT_CALL(myLatch, isActive())
        .Times(NUMBER_OF_CALLS)
        .WillOnce(Return(true));

    // Act
    // Сохраняю статус метода hardWareCheck() класса LockController
    HardWareStatus myHardWareStatus = myController.hardWareCheck();

    // Assert
    // Метод hardWareCheck() класса LockController вернёт HardWareStatus::OK
    ASSERT_EQ(HardWareStatus::OK, myHardWareStatus);
}

TEST(TestLab9, Test7) {
    // Arrange
    // Объект класса ILatch создан, валиден и передан в конструктор LockController
    MockKeypad myKeypad;
    MockLatch myLatch;
    // Вместо объекта класса IKeypad передан nullptr
    LockController myController(nullptr, &myLatch);

    // Prepare mocks
    // Метод isActive() класса IKeypad будет вызван ноль или более раз
    EXPECT_CALL(myKeypad, isActive())
        .Times(AtLeast(0))
        .WillOnce(Return(true));

    // Метод isActive() класса ILatch будет вызван ноль или более раз
    EXPECT_CALL(myLatch, isActive())
        .Times(AtLeast(0))
        .WillOnce(Return(true));

    // Act
    // Сохраняю статус метода hardWareCheck() класса LockController
    HardWareStatus myHardWareStatus = myController.hardWareCheck();

    // Assert
    // Метод hardWareCheck() класса LockController вернёт HardWareStatus::ERROR
    ASSERT_EQ(HardWareStatus::ERROR, myHardWareStatus);
}


TEST(TestLab9, Test8) {
    // Arrange
    // Объекты классов IKeypad и ILatch созданы, валидны
    // и переданы в конструктор LockController
    MockKeypad myKeypad;
    MockLatch myLatch;
    LockController myController(&myKeypad, &myLatch);

    // Prepare mocks
    // Метод isActive() класса IKeypad будет вызван ноль или более раз
    EXPECT_CALL(myKeypad, isActive())
        .Times(AtLeast(0))
        .WillOnce(Return(
                      // С клавиатурой (IKeypad) всё в порядке
                      true
                      ));

    // Метод isActive() класса ILatch будет вызван ноль или более раз
    EXPECT_CALL(myLatch, isActive())
        .Times(AtLeast(0))
        .WillOnce(Return(
                      // Задвижка (ILatch) не активна
                      false
                      ));

    // Act
    // Сохраняю статус метода hardWareCheck() класса LockController
    HardWareStatus myHardWareStatus = myController.hardWareCheck();

    // Assert
    // Метод hardWareCheck() класса LockController вернёт HardWareStatus::ERROR
    ASSERT_EQ(HardWareStatus::ERROR, myHardWareStatus);
}


TEST(TestLab9, Test9) {
    // Arrange
    MockKeypad myKeypad;
    MockLatch myLatch;
    // LockController только создан, поэтому установлен дефолтный пароль("0000")
    LockController myController(&myKeypad, &myLatch);

    // Создаю ответный пароль пользователя
    PasswordResponse userRespPass;
    // Статус "OK"
    userRespPass.status = PasswordResponse::Status::OK;
    // Пользователь вводит правильный пароль (когда у него попросят)
    userRespPass.password = "0000";


    // Prepare mocks
    // Метод requestPassword() класса IKeypad будет вызван один раз
    EXPECT_CALL(myKeypad, requestPassword())
        .Times(NUMBER_OF_CALLS)
        .WillOnce(Return(userRespPass));

    // Act
    // Сохраняю статус метода isCorrectPassword() класса LockController
    bool correctPassword = myController.isCorrectPassword();

    // Assert
    // Метод isCorrectPassword() класса LockController вернёт true
    ASSERT_TRUE(correctPassword);
}

TEST(TestLab9, Test10) {
    // Arrange
    MockKeypad myKeypad;
    MockLatch myLatch;
    // LockController только создан, поэтому установлен дефолтный пароль("0000")
    LockController myController(&myKeypad, &myLatch);

    // Создаю ответный пароль пользователя
    PasswordResponse userRespPass;
    // Статус "OK"
    userRespPass.status = PasswordResponse::Status::OK;
    // Пользователь вводит НЕ правильный пароль
    userRespPass.password = "1234";


    // Prepare mocks
    // Метод requestPassword() класса IKeypad будет вызван один раз
    EXPECT_CALL(myKeypad, requestPassword())
        .Times(NUMBER_OF_CALLS)
        .WillOnce(Return(userRespPass));

    // Act
    // Сохраняю статус метода isCorrectPassword() класса LockController
    bool correctPassword = myController.isCorrectPassword();

    // Assert
    // Метод isCorrectPassword() класса LockController вернёт false
    ASSERT_FALSE(correctPassword);
}


TEST(TestLab9, Test11) {
    // Arrange
    MockKeypad myKeypad;
    MockLatch myLatch;
    // LockController только создан, поэтому установлен дефолтный пароль("0000")
    LockController myController(&myKeypad, &myLatch);

    // Старый пароль вводится правильно
    PasswordResponse userRespPassOld;
    userRespPassOld.status = PasswordResponse::Status::OK;
    userRespPassOld.password = "0000";

    // Пользователь вводит новый пароль
    PasswordResponse userRespPassNew;
    userRespPassNew.status = PasswordResponse::Status::OK;
    userRespPassNew.password = "1234";


    // Prepare mocks
    EXPECT_CALL(myKeypad, requestPassword())
        // У пользователя просит пороль 3 раза
        .Times(3)
        // Будет запрошен старый пароль
        .WillOnce(Return(userRespPassOld))
        // Пользователь вводит новый пароль
        .WillOnce(Return(userRespPassNew))
        //Повторный ввод для подтверждения пароля
        .WillOnce(Return(userRespPassNew));

    // Act
    // Вызывается метод resetPassword() класса LockController
    myController.resetPassword();

    // Сохранение статуса правильности нового пароля
    bool correctPassword = myController.isCorrectPassword();

    // Assert
    // Проверка на правильность нового пароля
    ASSERT_TRUE(correctPassword);
}

TEST(TestLab9, Test12) {
    // Arrange
    MockKeypad myKeypad;
    MockLatch myLatch;
    LockController myController(&myKeypad, &myLatch);

    PasswordResponse userRespPassOld;
    userRespPassOld.status = PasswordResponse::Status::OK;
    userRespPassOld.password = "0000";  //Пользователь вводит правильный старый пароль

    //Пароль изменён на "9876"
    PasswordResponse userRespPassOldUpdate;
    userRespPassOldUpdate.status = PasswordResponse::Status::OK;
    userRespPassOldUpdate.password = "9876";

    PasswordResponse userRespPassNew;
    userRespPassNew.status = PasswordResponse::Status::OK;
    userRespPassNew.password = "1234";

    // Prepare mocks
    EXPECT_CALL(myKeypad, requestPassword())
        // Запрашиваю пароль у пользователя 5 раз
        .Times(5)
        //Запрашиваю старый пароль
        .WillOnce(Return(userRespPassOld))
        // Меняю пароль на "9876"
        .WillOnce(Return(userRespPassOldUpdate))
        // Проверяю его на правильность
        .WillOnce(Return(userRespPassOldUpdate))
        // Снова меняю пороль на "1234"
        .WillOnce(Return(userRespPassNew))
        // Проверяю его на правильность
        .WillOnce(Return(userRespPassNew));


// Act
    // Вызывается метод resetPassword() класса LockController два раза
    myController.resetPassword();
    myController.resetPassword();

    // Сохранение статуса правильности нового пароля
    bool correctPassword = myController.isCorrectPassword();

    // Assert
    // Проверка на правильность нового пароля
    ASSERT_TRUE(correctPassword);
}

#endif // TST_TESTDIVISIONBYZERO_H
