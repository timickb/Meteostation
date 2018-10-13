from telegram.ext import Updater, CommandHandler, MessageHandler, Filters
import requests
import json

TOKEN = "<bot-token>" # Telegram bot token
HOST = "0.0.0.0" # Server IP
PORT = 80 # Server port

def init_bot():
    # Инициализируем переменные
    updater = Updater(TOKEN)
    dp = updater.dispatcher

    print('Bot started.')

    # Добавляем обработчики сообщений
    dp.add_handler(CommandHandler('data', data))

    # Запускаем бота
    updater.start_polling()
    updater.idle()

def data(bot, update):
    res = requests.get('http://'+HOST+':'+PORT+'/')
    data = json.loads(res.text)
    message = 'Температура: %d, Влажность: %d' % (data['tmp'], data['hmd'])
    bot.sendMessage(update.message.from_user.id, message)


def main():
    print('Starting Telegram Bot...')
    init_bot()


if __name__ == "__main__":
    main()
