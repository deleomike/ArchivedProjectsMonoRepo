package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.shape.Box;
import javafx.stage.Stage;
import javafx.scene.paint.*;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.HBox;
import javafx.scene.shape.Rectangle;
import javafx.scene.control.SplitPane;
import javafx.scene.Group;
import javafx.stage.Stage;
import javafx.scene.control.Button;


public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{

        Rectangle rectangle = new Rectangle();
        rectangle.setWidth(100);
        rectangle.setHeight(100);
        rectangle.setArcHeight(10);
        rectangle.setWidth(10);
        HBox hbox = new HBox(20);
        hbox.setTranslateX(20);
        hbox.setTranslateY(20);

        SplitPane splitPane1 = new SplitPane();
        splitPane1.setPrefSize(200, 200);
        final Button l = new Button("Left Button");
        final Button r = new Button("Right Button");
        splitPane1.getItems().addAll(l, r);

        hbox.getChildren().add(splitPane1);

        Scene scene = new Scene(new Group(hbox), 560, 240);
        scene.setFill(Color.GHOSTWHITE);
        primaryStage.setScene(scene);
        primaryStage.setTitle("SplitPane");
        //primaryStage.setVisible(true);
        primaryStage.show();
//        Parent root = FXMLLoader.load(getClass().getResource("sample.fxml"));
//        primaryStage.setTitle("Hello World");
//        SplitPane primaryPane = new SplitPane();
//
//        StackPane sp1 = new StackPane(root);
//        sp1.getChildren().addAll(primaryPane);
//        Scene primaryScene = new Scene(,300,275,Color.BLACK);
//
//
//        primaryStage.setScene(primaryScene);
//        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}

/*
TERMINOLOGY:

Stage: the window
Scene: Content in the window
 */
