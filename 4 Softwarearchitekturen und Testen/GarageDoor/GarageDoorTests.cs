namespace GarageDoor;

public class GarageDoorTests
{
    [Theory]
    [InlineData(
        "open\nexit",
        "The door is closed\nOptions: 'open',  'lock', 'exit':\nThe door is opened\nOptions: 'close', 'exit':")]
    [InlineData(
        "lock\nstart unlock\n1234\nopen\nclose\nexit",
        "The door is closed\nOptions: 'open',  'lock', 'exit':\nThe door is locked\nOptions: 'start unlock', 'exit':\nEnter the combination:\nThe door is closed\nOptions: 'open',  'lock', 'exit':\nThe door is opened\nOptions: 'close', 'exit':\nThe door is closed\nOptions: 'open',  'lock', 'exit':")]
    [InlineData(
        "lock\nstart unlock\n1235\nexit",
        "The door is closed\nOptions: 'open',  'lock', 'exit':\nThe door is locked\nOptions: 'start unlock', 'exit':\nEnter the combination:\nThe door is locked\nOptions: 'start unlock', 'exit':")]
    public void TestGarageDoor(string input, string expectedOutput)
    {
        // Arrange
        var inputStream = new StringReader(input);
        var outputStream = new StringWriter();
        var controller = new Controller(inputStream, outputStream);

        // Act
        controller.Run();

        // Assert
        var res = outputStream.ToString().Trim();
        res.Should().Be(expectedOutput);
    }
}
