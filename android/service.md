## Service

```java
public class MyService extends Service {
    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        // 在后台执行任务
        new Thread(new Runnable() {
            @Override
            public void run() {
                performLongTask();
                stopSelf(); // 任务完成后停止服务
            }
        }).start();
        return START_STICKY; // 服务被杀死后重启
        //NOT_STICKY
        //DELEVER重启并传递Intent
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        // 进行清理操作
    }

    @Override
    public IBinder onBind(Intent intent) {
        // 如果不绑定服务，返回 null
        return null;
    }
}

```

`onCreate()`：服务首次创建时调用。

`onStartCommand()`：每次服务启动时调用。

`onDestroy()`：服务被销毁时调用。



## IntentService

```java
public class MyIntentService extends IntentService {

    // 必须有一个无参构造函数
    public MyIntentService() {
        super("MyIntentService");
    }

    @Override
    protected void onHandleIntent(Intent intent) {
        // 在这里执行耗时任务
        performLongTask();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        // 进行清理操作
    }
}

```

## 服务绑定

```java
public class MyBoundService extends Service {
    
    private final IBinder binder = new LocalBinder();
    
    public class LocalBinder extends Binder {
        MyBoundService getService() {
            // Return this instance of MyBoundService so clients can call public methods
            return MyBoundService.this;
        }
    }
    
    @Override
    public IBinder onBind(Intent intent) {
        return binder;
    }
    
    // Method to get the current system time
    public String getCurrentTime() {
        return DateFormat.format("yyyy-MM-dd HH:mm:ss", System.currentTimeMillis()).toString();
    }
}
```



```java
public class MainActivity extends AppCompatActivity {

    private MyBoundService myBoundService;
    private boolean isBound = false;
    private TextView timeTextView;

    private ServiceConnection connection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName className, IBinder service) {
            // We've bound to MyBoundService, cast the IBinder and get MyBoundService instance
            MyBoundService.LocalBinder binder = (MyBoundService.LocalBinder) service;
            myBoundService = binder.getService();
            isBound = true;
            // Update the UI with the current time
            updateTime();
        }

        @Override
        public void onServiceDisconnected(ComponentName arg0) {
            isBound = false;
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        timeTextView = findViewById(R.id.timeTextView);

        // Bind to MyBoundService
        Intent intent = new Intent(this, MyBoundService.class);
        bindService(intent, connection, Context.BIND_AUTO_CREATE);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        // Unbind from the service
        if (isBound) {
            unbindService(connection);
            isBound = false;
        }
    }

    private void updateTime() {
        if (isBound) {
            String currentTime = myBoundService.getCurrentTime();
            timeTextView.setText(currentTime);
        }
    }
}
```

