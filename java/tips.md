### 动态代理

```java
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

public class DynamicProxyExample {

    public static void main(String[] args) {
        // 创建真实对象
        MyInterface realObject = new MyInterfaceImpl();

        // 创建代理对象
        MyInterface proxy = (MyInterface) Proxy.newProxyInstance(
            MyInterface.class.getClassLoader(),
            new Class[]{MyInterface.class},
            new MyInvocationHandler(realObject)
        );

        // 调用代理对象的方法
        proxy.doSomething();
    }

    // 自定义InvocationHandler实现
    static class MyInvocationHandler implements InvocationHandler {
        private final MyInterface realObject;

        public MyInvocationHandler(MyInterface realObject) {
            this.realObject = realObject;
        }

        @Override
        public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
            // 在方法调用前执行自定义逻辑
            System.out.println("Before invoking " + method.getName());
            // 调用真实对象的方法
            Object result = method.invoke(realObject, args);
            // 在方法调用后执行自定义逻辑
            System.out.println("After invoking " + method.getName());
            return result;
        }
    }
}
```

